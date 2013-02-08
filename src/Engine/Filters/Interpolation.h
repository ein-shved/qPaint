#ifndef _ITERPOLATION_H
#define _ITERPOLATION_H

#include "../Filter.h"

/** @class Interpolation @{
 * Класс Interpolation является базовым для всех фильров, использующих
 * интерполяцию. Класс реализует метод launch, который к каждому пкселю
 * изображения применяет метод calcNeighbors(). Наследник должен реализовать
 * этот метод самостоятельно. Он должен вычислять новое положение указанного
 * пикселя, которое интерполируется классом Interpolation.
 */

class Interpolation : public Filter {
public:
	Interpolation (): Filter() {}
        Interpolation ( const Filter& filter): Filter (filter) {}
        Interpolation ( const Interpolation& filter): Filter (filter) {}
        explicit Interpolation ( const QRect &area): Filter(area) {}
        explicit Interpolation ( const Callback& callback): Filter (callback) {}
        Interpolation ( const QRect& area, const Callback& callback): Filter (area, callback){}

	QImage launch ( const QImage& in_Image ) const;
protected:
	struct Kernel {
		int x,y;
		int size;
		qreal resX, resY;
		qreal centrX, centrY;
		qreal deltaX, deltaY;
	private:
		const QImage& m_lImage;
	public:
		Kernel ( const QImage& in_Image, size_t in_size ): size (in_size), m_lImage(in_Image) {}
		inline QRgb operator () ( int in_x, int in_y ) const {
			return pixel ( m_lImage, x + in_x, y + in_y);
		}
		inline QRgb operator [] ( int in_index ) const {
			int in_y=in_index / size;
			in_index %= size;
			return pixel ( m_lImage, x+in_index, y + in_y);
		}
		static inline QRgb pixel (const QImage& in_Image, int x, int y )
		{
			if ( x<0 ) return 0;
			else if ( x >= in_Image.width() )
				return 0;
			if ( y<0 ) return 0;
			else if ( y >= in_Image.height() )
				return 0;
			return in_Image.pixel(x,y);
		}
		inline uint imageWidth () const {
			return m_lImage.width();
		}
		inline uint imageHeight () const {
			return m_lImage.height();
		}
	};
	virtual void calcNeighbors ( Kernel& in_Kernel ) const =0;
	virtual void calcGeometry ( const QImage& image, int& lWidth, int& lHeight ) const =0;
};

class Scaling : public Interpolation {
private:
	qreal m_fFactor;
	void m_fCalcSize ();
public:
	Scaling ( qreal in_fFactor = 1 );
        Scaling ( const Filter& filter, qreal in_fFactor = 1);
        Scaling ( const Scaling& filter);
        explicit Scaling ( const QRect &area, qreal in_fFactor = 1);
        explicit Scaling ( const Callback& callback, qreal in_fFactor = 1);
        Scaling ( const QRect& area, const Callback& callback, qreal in_fFactor = 1);

protected:
	void calcGeometry ( const QImage& image, int& lWidth, int& lHeight ) const;
	void calcNeighbors ( Interpolation::Kernel& in_Kernel ) const;
public:
	Scaling* copy() const;
};

class Rotation : public Interpolation {
private:
	struct RotationVector {
		qreal x,y;
		inline RotationVector (qreal in_x, qreal in_y) : x(in_x), y(in_y) {}
	};
	class RotationMatrix {
	private:
		qreal m_fAngle;
		qreal m_fCos, m_fSin;
		qreal m_fInfelicity;
	public:
		RotationMatrix ( qreal in_angle );
		RotationMatrix ( const RotationMatrix& other );
		inline RotationVector operator * ( const RotationVector& v) const {
			return RotationVector ( m_fCos * v.x + m_fSin * v.y,
						m_fCos * v.y - m_fSin * v.x);
		}
		inline qreal infelicity () const {
			return m_fInfelicity;
		}
	} const m_mRotationMatrix;
public:
	Rotation ( qreal in_Angle = 1 );
        Rotation ( const Filter& filter, qreal in_Angle = 1);
        Rotation ( const Rotation& filter);
        explicit Rotation ( const QRect &area, qreal in_Angle = 1);
        explicit Rotation ( const Callback& callback, qreal in_Angle = 1);
        Rotation ( const QRect& area, const Callback& callback, qreal in_Angle = 1);

protected:
	void calcGeometry ( const QImage& image, int& lWidth, int& lHeight ) const;
	void calcNeighbors ( Interpolation::Kernel& in_Kernel ) const;
public:
	Rotation* copy() const;
};

/**
 * @}
 */

#endif //_ITERPOLATION_H