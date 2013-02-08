#include "Supplementary.h"
#include <cstdlib>
#include <cmath>

Glass* Glass::copy () const {
	return new Glass (*this);
}

QImage Glass::launch ( const QImage& image ) const
{
	QRect area = getRealArea ( image );

        QImage imgNew(image.width(), image.height(), QImage::Format_RGB32);
	uint uiPercent, uiQuantum = image.width() * image.height() / 100;

	int iFactor = sqrt(image.width()*image.width() +
		      image.height()*image.height())/200;
	if ( iFactor <= 2 ) {
		iFactor = 3;
	}
	int iHalfFactor = iFactor/2;

	for (int y = 0; y < image.height(); ++y){
		for (int x = 0; x < image.width(); ++x){
			if ( area.contains(x,y) ) {
				int newX = x + rand()%iFactor - iHalfFactor;
				int newY = y + rand()%iFactor - iHalfFactor;

				if ( newX < 0 ) newX = 0;
				else if ( newX >= image.width() )
					newX = image.width() - 1;
				if ( newY < 0 ) newY = 0;
				else if ( newY >= image.height() )
					newY = image.height() - 1;

				imgNew.setPixel(x, y, image.pixel(newX,newY) );
			} else {
				imgNew.setPixel(x, y, image.pixel(x,y));
			}
                        uiPercent = y * image.width() + x;
                        if (uiPercent % uiQuantum == 0)
                                callback(uiPercent / uiQuantum);
                }
	}
	callback (100);
	return imgNew;
}