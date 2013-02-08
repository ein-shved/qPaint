#include "GreyWorld.h"

#include <iostream>
#include <limits>
#include <stdexcept>

GreyWorld* GreyWorld::copy () const
{
	return new GreyWorld (*this);
}

QImage GreyWorld::launch ( const QImage& in_Image ) const
{
	QRect area = getRealArea ( in_Image );
	GreyInfo sGrey = readGrey ( in_Image, area, 3);

	if ( sGrey.balance() ) {
		callback (100);
		return in_Image;
	}

	QImage imgNew(in_Image.width(), in_Image.height(), QImage::Format_RGB32);
	uint uiPercent, uiQuantum = in_Image.width() * in_Image.height() / 100;
	int avg = sGrey.avg();

	for (int y = 0; y < in_Image.height(); ++y){
		for (int x = 0; x < in_Image.width(); ++x){
			if ( area.contains(x,y) ) {
				QRgb rgb = in_Image.pixel(x, y);
				int colorR = qRed(rgb)*avg/sGrey.R;
				int colorG = qGreen(rgb)*avg/sGrey.G;
				int colorB = qBlue(rgb)*avg/sGrey.B;
				if ( colorR > 255) colorR = 255;
				else if ( colorR < 0 ) colorR = 0;
				if ( colorG > 255) colorG = 255;
				else if ( colorG < 0 ) colorG = 0;
				if ( colorB > 255) colorB = 255;
				else if ( colorB < 0 ) colorB = 0;
				imgNew.setPixel(x, y, qRgb (colorR, colorG, colorB ) );
			} else {
				imgNew.setPixel(x, y, in_Image.pixel(x,y));
			}
			uiPercent = y * in_Image.width() + x;
                        if (uiPercent % uiQuantum == 0)
                                callback(33+uiPercent*2 / (3*uiQuantum));
		}
	}
	callback (100);
	return imgNew;
}

GreyWorld::GreyInfo GreyWorld::readGrey ( const QImage& in_Image, const QRect& area,
			       int in_percentPart, int in_percentStart ) const
{
	uint uiPercent, uiQuantum = in_Image.width() * in_Image.height() / 100;
	unsigned long long r=0,g=0,b=0;
	unsigned long long counter = 0;

	unsigned long long max = std::numeric_limits<unsigned long long>::max();
	
	for (int y = 0; y < in_Image.height(); ++y){
		for (int x = 0; x < in_Image.width(); ++x){
			if ( area.contains(x,y) ) {
				QRgb rgb = in_Image.pixel(x, y);
				if ( max - qRed(rgb) < r || max - qGreen(rgb) < g || max - qBlue(rgb) < b || max - 1 < counter )
					throw std::logic_error ("Area is too big. Try to select smaller area.");
				
				++counter;
				r+=qRed(rgb);
				g+=qGreen(rgb);
				b+=qBlue(rgb);
			}
			uiPercent = y * in_Image.width() + x;
                        if (uiPercent % uiQuantum == 0)
				callback(in_percentStart+uiPercent / (in_percentPart*uiQuantum) );
		}
	}
	GreyInfo result;
	result.R = (int) (r/counter);
	result.G = (int) (g/counter);
	result.B = (int) (b/counter);

	return result;
}