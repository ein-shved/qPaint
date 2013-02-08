#include "Manually.h"
#include <stdexcept>
#include <iostream>

static inline int checkSize ( int size ) {
	if ( size<=0 )
		throw std::logic_error ("Manually: Wrong matrix size.\n");
	return size;
}
static inline int getHeight ( const Manually::Matrix& m ) {
	checkSize(m.size());
	return m[0].size();
}

Manually::Manually ( const Matrix& mKernel, int in_percentPart, int in_percentStart ) :
    Convolution(mKernel.size(),getHeight(mKernel)), m_mKernel (mKernel),
    m_iPercentPart (in_percentPart), m_iPercentStart ( in_percentStart)
{
	calcDelta();
}
Manually::Manually ( const Manually& filter, int in_percentPart, int in_percentStart ) :
    Convolution(filter, filter.m_mKernel.size(),getHeight(filter.m_mKernel)), m_mKernel (filter.m_mKernel),
    m_iPercentPart (in_percentPart), m_iPercentStart ( in_percentStart)
{
	calcDelta();
}
Manually::Manually ( const QRect &area, const Matrix& mKernel, int in_percentPart, int in_percentStart ) :
    Convolution(area,mKernel.size(),getHeight(mKernel)), m_mKernel (mKernel), m_iPercentPart (in_percentPart),
    m_iPercentStart ( in_percentStart)
{
	calcDelta();
}
Manually::Manually ( const Callback& callback, const Matrix& mKernel, int in_percentPart, int in_percentStart ) :
    Convolution(callback,mKernel.size(),getHeight(mKernel)), m_mKernel (mKernel), m_iPercentPart (in_percentPart),
    m_iPercentStart ( in_percentStart)
{
	calcDelta();
}
Manually::Manually ( const QRect& area, const Callback& callback, const Matrix& mKernel, int in_percentPart, int in_percentStart ) :
    Convolution(area, callback, mKernel.size(),getHeight(mKernel)), m_mKernel (mKernel), m_iPercentPart (in_percentPart),
    m_iPercentStart ( in_percentStart)
{
	calcDelta();
}
Manually::Manually ( const Filter& filter, const Matrix& mKernel, int in_percentPart, int in_percentStart ):
    Convolution(filter,mKernel.size(),getHeight(mKernel)), m_mKernel (mKernel), m_iPercentPart (in_percentPart), m_iPercentStart ( in_percentStart)
{
	calcDelta();
}

Manually* Manually::copy () const
{
	return new Manually(*this);
}

void Manually::calcDelta()
{
	m_fDelta = 0;
	for ( int x = 0 ;x < m_mKernel.size(); ++x ) {
		for ( int y = 0 ;y < m_mKernel[x].size(); ++y ) {
			m_fDelta += m_mKernel[x][y];
		}
	}
	if ( m_fDelta < 0.001 && m_fDelta > -0.001 ) {
		m_fDelta =1;
	}
}

void Manually::callback ( uint percent) const
{
	Filter::callback ( m_iPercentStart + percent/m_iPercentPart);
}

QRgb Manually::calcPixel ( const Convolution::Kernel& in_Kernel ) const
{
	//Trust code
	float resultR =0, resultG =0, resultB =0;
	for ( int x = 0 ;x < in_Kernel.width; ++x ) {
		for ( int y = 0 ;y < in_Kernel.height; ++y ) {
			QRgb rgb = in_Kernel(x,y);
			resultR += qRed (rgb)*m_mKernel[x][y];
			resultG += qGreen (rgb)*m_mKernel[x][y];
			resultB += qBlue (rgb)*m_mKernel[x][y];
		}
	}
	
	resultR /= m_fDelta;
	resultG /= m_fDelta;
	resultB /= m_fDelta;
	
	if ( resultR > 255 ) {
		resultR = 255;
	} else
	if ( resultR < 0 ) {
		resultR = 0;
	}

	if ( resultG > 255 ) {
		resultG = 255;
	} else
	if ( resultG < 0 ) {
		resultG = 0;
	}
	if ( resultB > 255 ) {
		resultB = 255;
	} else
	if ( resultB < 0 ) {
		resultB = 0;
	}
	return qRgb ( resultR, resultG, resultB );
}