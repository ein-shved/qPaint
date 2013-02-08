#ifndef _GAUSSIAN_SEPAR
#define _GAUSSIAN_SEPAR

#ifdef Use_Separable_Gauss
#include "../Filter.h"

class Gaussian : public Filter {
private:
	size_t m_size;
	float m_sigma;
public:
	Gaussian ( size_t in_size, float in_sigma );
        Gaussian ( const Filter& filter, size_t in_size, float in_sigma );
	Gaussian ( const Gaussian& filter);
        explicit Gaussian ( const QRect &area, size_t in_size, float in_sigma );
        explicit Gaussian ( const Callback& callback, size_t in_size, float in_sigma  );
        Gaussian ( const QRect& area, const Callback& callback, size_t in_size, float in_sigma );


        QImage launch ( const QImage& in_Image ) const;
        Gaussian* copy () const;
};
#endif //Use_Separable_Gauss

#endif //_GAUSSIAN_SEPAR