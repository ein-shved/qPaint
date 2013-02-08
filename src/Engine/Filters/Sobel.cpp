#include <stdexcept>
#include <iostream>
#include <cmath>

#include "Sobel.h"

Sobel::Sobel () : Convolution(3)
{};
Sobel::Sobel ( const Filter& filter) : Convolution(filter,3)
{};
Sobel::Sobel ( const QRect &area) :  Convolution(area,3)
{};
Sobel::Sobel ( const Callback& callback) :  Convolution(callback,3)
{};
Sobel::Sobel ( const QRect& area, const Callback& callback):  Convolution(area,callback,3)
{};
Sobel* Sobel::copy () const {
	return new Sobel(*this);
}

QRgb Sobel::calcPixel ( const Kernel& in_Kernel ) const {
	if ( in_Kernel.size != 3 ) {
		throw std::logic_error("Sobel: Unexpected kernel size.");
	}
	QRgb 	rgb02 =	in_Kernel(0,2), rgb00 = in_Kernel(0,0),
		rgb12 = in_Kernel(1,2), rgb10 = in_Kernel(1,0),
		rgb22 = in_Kernel(2,2), rgb20 = in_Kernel(2,0),

		rgb21 = in_Kernel(2,1), rgb01 = in_Kernel(0,1);

	int xGrad = 	      lightness(rgb02) - lightness(rgb00) +
			      2*lightness(rgb12) - 2*lightness(rgb10) +
			      lightness(rgb22) - lightness(rgb20);

	int yGrad = 	      lightness(rgb20) - lightness(rgb00) +
			      2*lightness(rgb21) - 2*lightness(rgb01) +
			      lightness(rgb22) - lightness(rgb02);
	return setLightness ( in_Kernel(1,1), sqrt (xGrad*xGrad + yGrad*yGrad));
}