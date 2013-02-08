#ifndef _MANUALLY_H
#define _MANUALLY_H

#include <QVector>
#include "Convolution.h"

class Manually : public Convolution {
public:
	typedef QVector<QVector<float> > Matrix;
private:
	float m_fDelta;
	Matrix m_mKernel;
	void calcDelta();
	int m_iPercentPart, m_iPercentStart;
public:
	Manually ( const Matrix& mKernel, int in_percentPart = 1, int in_percentStart = 0 );
        Manually ( const Manually& filter, int in_percentPart = 1, int in_percentStart = 0 );
        explicit Manually ( const QRect &area, const Matrix& mKernel, int in_percentPart = 1, int in_percentStart = 0 );
        explicit Manually ( const Callback& callback, const Matrix& mKernel, int in_percentPart = 1, int in_percentStart = 0 );
        Manually ( const QRect& area, const Callback& callback, const Matrix& mKernel, int in_percentPart = 1, int in_percentStart = 0 );
	Manually ( const Filter& filter, const Matrix& mKernel, int in_percentPart = 1, int in_percentStart = 0 );
private:
	void callback ( uint percent ) const;
	QRgb calcPixel ( const Convolution::Kernel& in_Kernel ) const;
public:
	Manually* copy () const;
};



#endif //_MANUALLY_H