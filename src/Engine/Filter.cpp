#include "Filter.h"
#include <QVector>

#include <iostream>

using namespace std;

Filter::Filter ()
{}
Filter::Filter ( const Filter &filter) :
        m_ImageArea (filter.m_ImageArea),
        m_Callback(filter.m_Callback)
{}
Filter::Filter ( const QRect &area ):
    m_ImageArea (area)
{}
Filter::Filter ( const Callback &callback ):
    m_Callback(callback)
{}
Filter::Filter ( const QRect &area, const Callback &callback ):
    m_ImageArea (area),
    m_Callback(callback)
{}

QRect Filter::getRealArea ( const QImage &in_Image ) const
{
	if ( m_ImageArea.isNull() || !m_ImageArea.isValid() ) {
		return in_Image.rect();
	} else {
		return m_ImageArea;
	}
}
bool Filter::isAreaOk () const
{
	return !(m_ImageArea.isNull() || !m_ImageArea.isValid());
}

QImage Grayscale::launch ( const QImage& image) const
{
	QRect area = getRealArea ( image );

        QImage imgNew(image.width(), image.height(), QImage::Format_RGB32);
	uint uiPercent, uiQuantum = image.width() * image.height() / 100;

	for (int y = 0; y < image.height(); ++y){
		for (int x = 0; x < image.width(); ++x){
			if ( area.contains(x,y) ) {
				QRgb rgb = image.pixel(x, y);
				uint uiGray = 0.2125*qRed(rgb) + 0.7154*qGreen(rgb) + 0.0721*qBlue(rgb);
				imgNew.setPixel(x, y, qRgb(uiGray,uiGray,uiGray) );
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

Grayscale* Grayscale::copy() const
{
	return new Grayscale (*this);
}
