#include "Convolution.h"
#include <vector>
#include <QColor>
#include <algorithm>
#include <cmath>
#include <iostream>

QImage Convolution::launch ( const QImage& in_Image ) const
{
	QRect area = getRealArea ( in_Image );

	QImage imgNew(in_Image.width(), in_Image.height(), QImage::Format_RGB32);
	uint uiPercent, uiQuantum = in_Image.width() * in_Image.height() / 100;

	Kernel mKernel ( in_Image, m_width, m_height );

	for (int y = 0; y < in_Image.height(); ++y){
		for (int x = 0; x < in_Image.width(); ++x){
			if ( area.contains(x,y) ) {
				mKernel.x=x;
				mKernel.y=y;
				imgNew.setPixel(x, y, calcPixel(mKernel) );
			} else {
				imgNew.setPixel(x, y, in_Image.pixel(x,y));
			}
			uiPercent = y * in_Image.width() + x;
                        if (uiPercent % uiQuantum == 0)
                                callback(uiPercent / (uiQuantum));
		}
	}
	callback (100);
	return imgNew;
}

Median* Median::copy() const
{
	return new Median(*this);
}
QImage Median::launch ( const QImage& in_Image ) const
{
	if ( getSize() <= 1 ) {
		callback (100);
		return in_Image;
	}
	return Convolution::launch (in_Image);
}

Median::Median ( size_t in_size ): Convolution(in_size) {
	m_vSorter.reserve(in_size*in_size);
}
Median::Median ( const Convolution& filter): Convolution(filter) {
	m_vSorter.reserve(getSize()*getSize());
}
Median::Median ( const QRect &area, size_t in_size ): Convolution(area, in_size) {
	m_vSorter.reserve(in_size*in_size);
}
Median::Median ( const Callback& callback, size_t in_size ): Convolution(callback, in_size) {
	m_vSorter.reserve(in_size*in_size);
}
Median::Median ( const QRect& area, const Callback& callback, size_t in_size ): Convolution(area,callback, in_size) {
	m_vSorter.reserve(in_size*in_size);
}
QRgb Median::calcPixel ( const Convolution::Kernel& in_Kernel ) const
{
	//TODO найти более эффективный алгоритм

	/*std::vector <pixelLightSort> sort;
	sort.reserve(in_Kernel.size*in_Kernel.size);

	for ( int y = 0; y< in_Kernel.size; ++y ) {
		for ( int x = 0; x< in_Kernel.size; ++x ) {
			sort.push_back (in_Kernel(x,y));
		}
	}
	std::sort ( sort.begin(), sort.end());

	return sort[in_Kernel.size*in_Kernel.size/2].rgb; */
	std::vector <short> sortR;
	std::vector <short> sortG;
	std::vector <short> sortB;

	sortR.reserve(in_Kernel.size*in_Kernel.size);
	sortG.reserve(in_Kernel.size*in_Kernel.size);
	sortB.reserve(in_Kernel.size*in_Kernel.size);
	//sort.reserve(in_Kernel.size*in_Kernel.size);

	for ( int y = 0; y< in_Kernel.size; ++y ) {
		for ( int x = 0; x< in_Kernel.size; ++x ) {
			QRgb rgb = in_Kernel(x,y);
			sortR.push_back (qRed(rgb));
			sortG.push_back (qGreen(rgb));
			sortB.push_back (qBlue(rgb));
		}
	}
	std::sort ( sortR.begin(), sortR.end());
	std::sort ( sortG.begin(), sortG.end());
	std::sort ( sortB.begin(), sortB.end());

	return qRgb ( sortR[in_Kernel.size*in_Kernel.size/2],
		      sortG[in_Kernel.size*in_Kernel.size/2],
		      sortB[in_Kernel.size*in_Kernel.size/2] );
}

#ifndef Use_Separable_Gauss

Gaussian* Gaussian::copy() const
{
	return new Gaussian(*this);
}
#ifndef PI
#define PI 3.14159
#endif

void Gaussian::calcFactors ()
{
	m_mFactors.clear();
	int size=getSize();
	float qSigma=m_sigma*m_sigma;
	m_mFactors.reserve(size);
	m_fFactorsSumm = 0;
	for ( int y = 0; y< size; ++y ) {
		m_mFactors.append(QVector<float>());
		m_mFactors[y].reserve(size);
		for ( int x = 0; x< size; ++x ) {
			float xDist = abs ( size/2 - x );
			float yDist = abs ( size/2 - y );
			float f = exp(- (xDist*xDist+yDist*yDist) / (2*qSigma)) / (2*PI*qSigma);
			m_fFactorsSumm +=f;
			m_mFactors[y].append (f);
		}
	}

}

QImage Gaussian::launch ( const QImage& in_Image ) const {
	return Convolution::launch (in_Image);
}

QRgb Gaussian::calcPixel ( const Convolution::Kernel& in_Kernel ) const
{
	float resultR=0, resultG=0, resultB=0;
	for ( int y=0; y < in_Kernel.size; ++y) {
		for ( int x=0; x < in_Kernel.size; ++x ) {
			float f = factorOf (x,y);
			QRgb rgb = in_Kernel(x,y);
			resultR += f*(float)qRed(rgb);
			resultG += f*(float)qGreen(rgb);
			resultB += f*(float)qBlue(rgb);
		}
	}
	resultR/=m_fFactorsSumm;
	resultG/=m_fFactorsSumm;
	resultB/=m_fFactorsSumm;
	if ( resultR >255 ) {
		resultR = 255;
	}
	if ( resultG >255 ) {
		resultG = 255;
	}
	if ( resultB >255 ) {
		resultB = 255;
	}
	return qRgb (resultR,resultG,resultB);
}


#endif //Use_Separable_Gauss