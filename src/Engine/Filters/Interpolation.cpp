#include <cmath>
#include "Interpolation.h"
#include <iostream>
QImage Interpolation::launch ( const QImage& in_Image ) const
{
	QRect area = getRealArea ( in_Image );

	int width=in_Image.width(), height=in_Image.height();
	Kernel mKernel ( in_Image, 2 );
	
	if ( !isAreaOk() ) {
		mKernel.centrX = ((qreal)width)/2;
		mKernel.centrY = ((qreal)height)/2;
		mKernel.deltaX = ((qreal)width)/2;
		mKernel.deltaY = ((qreal)height)/2;

		calcGeometry ( in_Image, width, height );
		area = QRect ( 0,0,width,height);
	} else {

		mKernel.centrX = ((qreal)area.width())/2 + area.x();
		mKernel.centrY = ((qreal)area.height())/2 + area.y();
		mKernel.deltaX = 0;
		mKernel.deltaY = 0;
	}
	QImage imgNew = QImage(width, height, QImage::Format_RGB32);
	uint uiPercent, uiQuantum = width * height / 100;

	for (int y = 0; y < height; ++y){
		for (int x = 0; x < width; ++x){
			if ( area.contains (x,y) ) {
				mKernel.size = 2;
				mKernel.x=x;
				mKernel.y=y;
				calcNeighbors(mKernel);

				float dx1 = ((float)mKernel.x) + 1 - mKernel.resX;
				float dx2 = mKernel.resX - ((float)mKernel.x);
				float dy1 = ((float)mKernel.y) + 1 - mKernel.resY;
				float dy2 = mKernel.resY - ((float)mKernel.y);
				QRgb rgb00 = mKernel(0,0);
				QRgb rgb01 = mKernel(0,1);
				QRgb rgb10 = mKernel(1,0);
				QRgb rgb11 = mKernel(1,1);

				int r = (qRed(rgb00)*dx1 + qRed(rgb10)*dx2)*dy1 +
					(qRed(rgb01)*dx1 + qRed(rgb11)*dx2)*dy2;

				int g = (qGreen(rgb00)*dx1 + qGreen(rgb10)*dx2)*dy1 +
					(qGreen(rgb01)*dx1 + qGreen(rgb11)*dx2)*dy2;

				int b = (qBlue(rgb00)*dx1 + qBlue(rgb10)*dx2)*dy1 +
					(qBlue(rgb01)*dx1 + qBlue(rgb11)*dx2)*dy2;

				if ( r > 255 ) {
					r = 255;
				} else if ( r < 0 ) {
					r = 0;
				}
				if ( g > 255 ) {
					g = 255;
				} else if ( g < 0 ) {
					g = 0;
				}
				if ( b > 255 ) {
					b = 255;
				} else if ( b < 0 ) {
					b = 0;
				}


				imgNew.setPixel(x, y, qRgb (r,g,b ) );
			} else {
				imgNew.setPixel(x, y, in_Image.pixel(x,y));
			}
			uiPercent = y * width + x;
                        if (uiPercent % uiQuantum == 0)
                                callback(uiPercent / (uiQuantum));
		}
	}
	callback (100);
	return imgNew;
}

Scaling::Scaling ( qreal in_fFactor): Interpolation(), m_fFactor(in_fFactor)
{}
Scaling::Scaling ( const Filter& filter, qreal in_fFactor) : Interpolation(filter), m_fFactor(in_fFactor)
{}
Scaling::Scaling ( const Scaling& filter) : Interpolation(filter), m_fFactor(filter.m_fFactor)
{}
Scaling::Scaling ( const QRect &area, qreal in_fFactor) : Interpolation(area), m_fFactor(in_fFactor)
{}
Scaling::Scaling ( const Callback& callback, qreal in_fFactor) : Interpolation(callback), m_fFactor(in_fFactor)
{}
Scaling::Scaling ( const QRect& area, const Callback& callback, qreal in_fFactor) : Interpolation(area, callback), m_fFactor(in_fFactor)
{}

Scaling* Scaling::copy() const
{
	return new Scaling(*this);
}

void Scaling::calcGeometry ( const QImage& image, int& lWidth, int& lHeight ) const
{
	lWidth = image.width()*m_fFactor;
	lHeight = image.height()*m_fFactor;
}
void Scaling::calcNeighbors ( Interpolation::Kernel& in_Kernel ) const
{
	qreal x = in_Kernel.centrX - in_Kernel.deltaX +
			(in_Kernel.x - in_Kernel.centrX + in_Kernel.deltaX)/m_fFactor;
	qreal y = in_Kernel.centrY - in_Kernel.deltaY +
			(in_Kernel.y - in_Kernel.centrY + in_Kernel.deltaY)/m_fFactor;
	in_Kernel.x = x;
	in_Kernel.y = y;
	in_Kernel.resX = x;
	in_Kernel.resY = y;
}


Rotation::Rotation ( qreal in_Angle) :
    Interpolation(), m_mRotationMatrix(in_Angle)
{}
Rotation::Rotation ( const Filter& filter, qreal in_Angle) :
    Interpolation(filter), m_mRotationMatrix(in_Angle)
{}
Rotation::Rotation ( const Rotation& filter) :
    Interpolation(filter), m_mRotationMatrix(filter.m_mRotationMatrix)
{}
Rotation::Rotation ( const QRect &area, qreal in_Angle) :
    Interpolation(area), m_mRotationMatrix(in_Angle)
{}
Rotation::Rotation ( const Callback& callback, qreal in_Angle) :
    Interpolation(callback), m_mRotationMatrix(in_Angle)
{}
Rotation::Rotation ( const QRect& area, const Callback& callback, qreal in_Angle) :
    Interpolation(area, callback), m_mRotationMatrix(in_Angle)
{}

#ifndef PI
#define PI 3.14159265359
#endif //PI

Rotation::RotationMatrix::RotationMatrix ( qreal in_Angle ) :
    m_fAngle(in_Angle), m_fCos (cos(in_Angle)), m_fSin(sin(in_Angle)), m_fInfelicity ( in_Angle*0.25/PI )
{}
Rotation::RotationMatrix::RotationMatrix ( const Rotation::RotationMatrix& other ) :
    m_fAngle(other.m_fAngle), m_fCos (other.m_fCos), m_fSin(other.m_fSin), m_fInfelicity ( other.m_fInfelicity )
{}

void Rotation::calcGeometry ( const QImage& image, int& lWidth, int& lHeight ) const {
	lWidth = image.width();
	lHeight = image.height();
}
Rotation* Rotation::copy() const {
	return new Rotation(*this);
}
void Rotation::calcNeighbors ( Interpolation::Kernel& in_Kernel ) const
{
	RotationVector v ( ((qreal)in_Kernel.x) - in_Kernel.centrX, ((qreal)in_Kernel.y) - in_Kernel.centrY );
	v = m_mRotationMatrix * v;
	qreal x = in_Kernel.centrX + v.x;
	qreal y = in_Kernel.centrY + v.y;
	in_Kernel.resX = x;
	in_Kernel.resY = y;
	//if ( x>0 ) x+=m_mRotationMatrix.infelicity(); //погрешности.
	//if ( y>0 ) y+=m_mRotationMatrix.infelicity();
	in_Kernel.x = x;
	in_Kernel.y = y;
}

