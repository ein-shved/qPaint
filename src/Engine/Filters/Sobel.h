#ifndef _SOBEL_H
#define _SOBEL_H


#include "Convolution.h"

class Sobel : public Convolution {
public:
	Sobel ();
        Sobel ( const Filter& filter);
        explicit Sobel ( const QRect &area);
        explicit Sobel ( const Callback& callback);
        Sobel ( const QRect& area, const Callback& callback);

	QRgb calcPixel ( const Kernel& in_Kernel ) const;
	Sobel* copy() const;
};



#endif //_SOBEL_H