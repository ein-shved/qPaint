#ifdef Use_Separable_Gauss

#include "GaussianS.h"
#include "Manually.h"
#include <cmath>
#include <iostream>

Gaussian::Gaussian ( size_t in_size, float in_sigma) : Filter(), m_size(in_size), m_sigma(in_sigma)
{}
Gaussian::Gaussian ( const Filter& filter, size_t in_size, float in_sigma) : Filter(filter), m_size(in_size), m_sigma(in_sigma)
{}
Gaussian::Gaussian ( const Gaussian& filter) : Filter(filter), m_size (filter.m_size), m_sigma(filter.m_sigma)
{}
Gaussian::Gaussian ( const QRect &area, size_t in_size, float in_sigma) : Filter(area), m_size(in_size), m_sigma(in_sigma)
{}
Gaussian::Gaussian ( const Callback& callback, size_t in_size, float in_sigma ) : Filter(callback), m_size(in_size), m_sigma(in_sigma)
{}
Gaussian::Gaussian ( const QRect& area, const Callback& callback, size_t in_size, float in_sigma ) : Filter(area,callback),
    m_size(in_size), m_sigma(in_sigma)
{}


#ifndef PI
#define PI 3.14159
#endif

QImage Gaussian::launch ( const QImage& in_Image ) const
{
	float qSigma = m_sigma*m_sigma;
	QVector<QVector<float> > matrixRaw;
	for ( int x = 0; x< (int)m_size; ++x ) {
		matrixRaw.append ( QVector<float> () );
		float xDist = abs ( m_size/2 - x );
		float f = exp(- (xDist*xDist) / (2*qSigma)) / (2*PI*qSigma);
		matrixRaw[x].append ( f );
	}
	QVector<QVector<float> > matrixColumn;
	matrixColumn.append ( QVector<float> () );
	for ( int y = 0; y< (int)m_size; ++y ) {
		float yDist = abs ( m_size/2 - y );
		float f = exp(- (yDist*yDist) / (2*qSigma)) / (2*PI*qSigma);
		matrixColumn[0].append ( f );
	}
	
	Manually mRaw ( *this, matrixRaw, 2);
	Manually mColumn ( *this, matrixColumn,2, 50);

	return mColumn.launch (mRaw.launch(in_Image));
}
Gaussian* Gaussian::copy () const
{
	return new Gaussian (*this);
}

#endif //Use_Separable_Gauss