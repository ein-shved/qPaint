#include "Hystogram.h"
#include <QColor>

#include <iostream>
#include <stdexcept>

Hystogram::HystogramInfo Hystogram::readHystogram (const QImage& in_Image, const QRect& in_Area, int extra,
						   int in_percentPart, int in_percentStart ) const
{
	HystogramInfo vHystogram;
	
	uint uiPercent, uiQuantum = in_Image.width() * in_Image.height() / 100;
	bool first;
	
	for (int y = 0; y < in_Image.height(); ++y) {
		for (int x = 0; x < in_Image.width(); ++x) {
			if ( in_Area.contains(x,y) ) {
				QRgb rgb = in_Image.pixel(x, y);
				int l = getInterestValue (rgb, extra);
				if ( first) {
					vHystogram.min=l;
					vHystogram.max=l;
					first = false;
				} else {
					if ( vHystogram.min>l) {
						vHystogram.min=l;
					}
					if (vHystogram.max<l) {
						vHystogram.max=l;
					}
				}
				++vHystogram.hystogram[l];
			}
			uiPercent = y * in_Image.width() + x;
                        if (uiPercent % uiQuantum == 0)
                                callback(in_percentStart + uiPercent / (in_percentPart*uiQuantum));
		}
	}
	return vHystogram;
}

int HystogramLinear::getInterestValue (QRgb in_RGB, int) const
{
	return QColor(in_RGB).lightness();
}

Hystogram* HystogramLinear::copy () const
{
	return new HystogramLinear(*this);
}

QImage HystogramLinear::launch ( const QImage& in_Image ) const
{
	QRect area = getRealArea ( in_Image );
	HystogramInfo vHystogram = readHystogram ( in_Image, area, 0, 2, 0 );

	if ( ( (vHystogram.min == 0) && (vHystogram.max == 255) ) || ( vHystogram.min == vHystogram.max) ) {
		callback (100);
		return in_Image;
	}

	QImage imgNew(in_Image.width(), in_Image.height(), QImage::Format_RGB32);
	uint uiPercent, uiQuantum = in_Image.width() * in_Image.height() / 100;

	for (int y = 0; y < in_Image.height(); ++y){
		for (int x = 0; x < in_Image.width(); ++x){
			if ( area.contains(x,y) ) {
				QRgb rgb = in_Image.pixel(x, y);
				int colorL_old = lightness(rgb);
				int colorL_new = (colorL_old - vHystogram.min) * 255 /(vHystogram.max - vHystogram.min);
				
				imgNew.setPixel(x, y, setLightness (rgb, colorL_new, colorL_old) );
			} else {
				imgNew.setPixel(x, y, in_Image.pixel(x,y));
			}
			uiPercent = y * in_Image.width() + x;
                        if (uiPercent % uiQuantum == 0)
                                callback(50+uiPercent / (2*uiQuantum));
		}
	}
	callback (100);
	return imgNew;
}

int HystogramPerChennel::getInterestValue (QRgb in_RGB, int chennel) const
{
	switch (chennel) {
	case red:
		return qRed(in_RGB);
		break;
	case green:
		return qGreen(in_RGB);
		break;
	case blue:
		return qBlue(in_RGB);
		break;
	default:
		throw std::logic_error ("Wrong RGB channel.");
	}
}

Hystogram* HystogramPerChennel::copy () const
{
	return new HystogramPerChennel(*this);
}

QImage HystogramPerChennel::launch ( const QImage& in_Image ) const
{
	QRect area = getRealArea ( in_Image );

	HystogramInfo vRedHystogram = readHystogram ( in_Image, area, red, 5, 0 );
	HystogramInfo vGreenHystogram = readHystogram ( in_Image, area, green, 5, 20 );
	HystogramInfo vBlueHystogram = readHystogram ( in_Image, area, blue, 5, 40  );

	bool redFull = false,  greenFull = false, blueFull = false;
	if ( ( (vRedHystogram.min == 0) && (vRedHystogram.max == 255) ) || ( vRedHystogram.min == vRedHystogram.max) ) {
		redFull = true;
	}
	if ( ( (vBlueHystogram.min == 0) && (vBlueHystogram.max == 255) ) || ( vBlueHystogram.min == vBlueHystogram.max) ) {
		greenFull = true;
	}
	if ( ( (vGreenHystogram.min == 0) && (vGreenHystogram.max == 255) ) || ( vGreenHystogram.min == vGreenHystogram.max) ) {
		blueFull =true;
	}
	if ( redFull && greenFull && blueFull ) {
		callback(100);
		return in_Image;
	}

	QImage imgNew(in_Image.width(), in_Image.height(), QImage::Format_RGB32);
	uint uiPercent, uiQuantum = in_Image.width() * in_Image.height() / 100;

	for (int y = 0; y < in_Image.height(); ++y){
		for (int x = 0; x < in_Image.width(); ++x){
			if ( area.contains(x,y) ) {
				QRgb rgb = in_Image.pixel(x, y);
				int colorR = (redFull) ? qRed(rgb) : (qRed(rgb) - vRedHystogram.min) * 255 /(vRedHystogram.max - vRedHystogram.min);
				int colorG = (greenFull) ? qGreen(rgb) : (qGreen(rgb) - vRedHystogram.min) * 255 /(vGreenHystogram.max - vGreenHystogram.min);
				int colorB = (blueFull) ? qBlue(rgb) : (qBlue(rgb) - vBlueHystogram.min) * 255 /(vBlueHystogram.max - vBlueHystogram.min);
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
                                callback(60+uiPercent / (5*uiQuantum));
		}
	}
	callback (100);
	return imgNew;
}
