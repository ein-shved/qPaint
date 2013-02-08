#ifndef _CONVOLUTION_H
#define _CONVOLUTION_H

#include "../Filter.h"

#include <stdexcept>
#include <QVector>
#include <QColor>

/** @class Convolution @{
 * Класс Convolution является базовым для всех матричных фильров свертки.
 * Класс реализует метод launch, который к каждому пкселю изображения
 * применяет метод calcPixel() и передает ему матрицу окружения рассматриваемого
 * пикселя. Наследник должен реализовать этот метод самостоятельно, например,
 * медианный фильтр вычисляет среднее значение светлоты пикселя в матрице.
 *
 * К сожалению, в силу использования динамического полиморфизма на каждом
 * пикселе изображения, фильтры, использующие эту схему работают относительно
 * медленно.
 */

class Convolution : public Filter {

private:
	size_t m_width, m_height;
	size_t inline check_size ( size_t in_size ) {
		if ( in_size < 1 ) {
			throw std::logic_error ("Wrong matrix size.");
		}
		return in_size;
	}
public:
        Convolution ( size_t in_width = 1, size_t in_height = 0 ): Filter(),
		m_width (check_size(in_width)), m_height (in_height) {}
        Convolution ( const Filter& filter, size_t in_width = 1, size_t in_height = 0): Filter (filter),
		m_width (in_width), m_height (in_height) {}
        Convolution ( const Convolution& filter): Filter (filter),
		m_width (filter.m_width), m_height (filter.m_height) {}
        explicit Convolution ( const QRect &area, size_t in_width = 1, size_t in_height = 0 ): Filter(area),
		m_width (check_size(in_width)), m_height (in_height) {}
        explicit Convolution ( const Callback& callback, size_t in_width = 1, size_t in_height = 0 ): Filter (callback),
		m_width (check_size(in_width)), m_height (in_height) {}
        Convolution ( const QRect& area, const Callback& callback, size_t in_width = 1, size_t in_height = 0 ): Filter (area, callback),
		m_width (check_size(in_width)), m_height (in_height) {}

protected:
	struct Kernel {
		int x,y;
		int size;
		int width, height;
	private:
		const QImage& m_lImage;
	public:
		Kernel ( const QImage& in_Image, size_t in_width, size_t in_height = 0 ): size (in_width), width(in_width), height (in_height),
			m_lImage(in_Image) {}
		inline QRgb operator () ( int in_x, int in_y ) const {
			return pixel ( m_lImage, x - size/2 + in_x, y - size/2 + in_y);
		}
		inline QRgb operator [] ( int in_index ) const {
			int in_y=in_index / size;
			in_index %= size;
			return pixel ( m_lImage, x - size/2 + in_index, y - size/2 + in_y);
		}
		static inline QRgb pixel (const QImage& in_Image, int x, int y )
		{
			if ( x<0 ) x= -x;
			else if ( x >= in_Image.width() )
				x = 2 * in_Image.width() - x - 1;
			if ( y<0 ) y=-y;
			else if ( y >= in_Image.height() )
				y = 2 * in_Image.height() - y - 1;
			return in_Image.pixel(x,y);
		}
	};

	virtual QRgb calcPixel ( const Kernel& in_Kernel ) const =0;
	inline size_t getSize() const {
		return m_width;
	}
public:
        QImage launch ( const QImage& in_Image ) const;
};


class Median : public Convolution {
public:
	Median ( size_t in_size = 1 );
        Median ( const Convolution& filter);
        explicit Median ( const QRect &area, size_t in_size = 1 );
        explicit Median ( const Callback& callback, size_t in_size = 1 );
        Median ( const QRect& area, const Callback& callback, size_t in_size = 1 );
private:
	struct pixelLightSort{
		QRgb rgb;
		int lightness;
		pixelLightSort (QRgb in_rgb): rgb(in_rgb), lightness(Filter::lightness(rgb)) {}
		pixelLightSort (): rgb(0),lightness(0) {}
		inline bool operator < ( const pixelLightSort& other ) const {
			return lightness < other.lightness;
		}
		inline bool operator > ( const pixelLightSort& other ) const {
			return lightness > other.lightness;
		}
	};
	std::vector <pixelLightSort> m_vSorter;
	QRgb calcPixel ( const Convolution::Kernel& in_Kernel ) const;
public:
	Median* copy () const;
	QImage launch ( const QImage& in_Image ) const;
};

#ifndef Use_Separable_Gauss
class Gaussian : public  Convolution {
private:
	float m_sigma;

	typedef QVector< QVector<float> > Factors;
	Factors m_mFactors;
	float m_fFactorsSumm;
	inline float factorOf ( int x, int y ) const {
		return m_mFactors[y][x];
	}
	void calcFactors ();
public:
	Gaussian ( size_t in_size = 1, float in_sigma = 1 ): Convolution(in_size), m_sigma(in_sigma) {
		calcFactors ();
	};
        Gaussian ( const Convolution& filter, float in_sigma = 1): Convolution(filter), m_sigma(in_sigma) {
		calcFactors ();
	}
        explicit Gaussian ( const QRect &area, size_t in_size = 1, float in_sigma = 1 ): Convolution(area, in_size), m_sigma(in_sigma) {
		calcFactors ();
	}
        explicit Gaussian ( const Callback& callback, size_t in_size = 1, float in_sigma = 1 ): Convolution(callback, in_size), m_sigma(in_sigma) {
		calcFactors ();
	}
        Gaussian ( const QRect& area, const Callback& callback, size_t in_size = 1, float in_sigma = 1 ): Convolution(area,callback, in_size), m_sigma(in_sigma) {
		calcFactors ();
	}
private:
	QRgb calcPixel ( const Convolution::Kernel& in_Kernel ) const;
public:
	Gaussian* copy () const;
	QImage launch ( const QImage& in_Image ) const;
};

#endif //Use_Separable_Gauss

/**
 * @}
 */

#endif //_CONVOLUTION_H