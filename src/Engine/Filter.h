#ifndef _FILTER_H
#define _FILTER_H

#include <QImage>
#include <QColor>
#include "Callback.h"
#include <algorithm>

#define _INLINE_CALLBACK_

class Callback;

/** @class Filter @{
 *
 * Абстрактный класс Filter является шаблоном для фильтров, которые
 * будут действовать на изображение. В области m_ImageArea и сообщать
 * о ходе работы посредством m_Callback.
 */

class Filter {

private:
	QRect m_ImageArea; // считаем, что isNull() Прямоугольник обозначает всю картинку.
        Callback m_Callback;

public:
	/**
	 * @name Constructors
	 * По умолчанию устанавличает m_Callback по умолчанию (информация
	 * никуда не отправляется), m_ImageArea покрывает все изображение.
	 *
	 * @param in_Area
	 * Конструктор копирует area в m_ImageArea.
	 *
	 * @param in_Callback
	 * Конструктор копирует callback в m_Callback.
	 */
	Filter ();
        Filter ( const Filter& filter);
	explicit Filter ( const QRect& in_Area );
	explicit Filter ( const Callback& in_Callback );
	Filter ( const QRect& in_Area, const Callback& in_Callback );

	/**
	 * @name Setters
	 *
	 * setArea() устанавливает область действия фильтра m_ImageArea.
	 * @param in_Area
	 *
	 * setCallback() устанавливает m_Callback.
	 * @param in_Callback
	 */
	void inline setArea ( const QRect &in_Area ) {
                m_ImageArea = in_Area;
	}
	void inline setCallback ( const Callback& in_Callback ) {
		m_Callback = in_Callback;
	}

	/**
	 * @name Getters
	 * 
	 * getCallback() возвращает Callback
	 * 
	 */
	const Callback& getCallback () const {
		return m_Callback;
	}

	/**
	 * Метод launch() запускает работу фильтра.
	 * @param image
	 *
	 * Метод launch() запускает работу фильтра над изображением image.
	 * @return обработанная копия image.
	 *
	 * @todo Метод должен быть реализован наследниками.
	 */
	virtual QImage launch ( const QImage &in_Image ) const = 0;

	/**
	 * Метод getRealArea() возвращает фактическую область.
	 * @param image
	 *
	 * Метод getRealArea() возвращает фактическую область изображения
	 * image относительно _imageArea. Это означает:
	 * @if m_ImageArea.isNull
	 * 	@return область, охватывающая все изображение image;
	 * @else
	 * 	@return копия _imageArea.
	 */
	QRect getRealArea ( const QImage &in_Image ) const;

	/**
	 * Метод isAreaOk() определяет, является область частной, или охватывает
	 * все изображение.
	 */
	bool isAreaOk ( ) const;


	/**
	 * Метод callback() вызывает m_Callback.
	 * @param percent
	 *
	 * Метод callback() вызывает _callback c параметром percent. Является
	 * точкой доступа для наследников к вызову _callback.
	 */
protected:
#ifdef Inline_Callback
	inline void callback ( uint percent ) const {
		m_Callback (percent);
        }
#else //Inline_Callback
# ifdef Virtual_Callback
	virtual void callback ( uint percent ) const {
		m_Callback (percent);
        }
# else //Virtual_Callback
	void callback ( uint percent ) const {
		m_Callback (percent);
	}
# endif //Virtual_Callback
#endif //Inline_Callback

	/** @{
	 * @name lghtness
	 * 
	 * Статический метод lightness () вычисляет яркость.
	 * @param rgb
	 *
	 * Статический метод lightness () вычисляет яркость пикселя rgb.
	 */
        static inline int lightness (QRgb rgb) {
		//int l = 0.2125*qRed(rgb) + 0.7154*qGreen(rgb) + 0.0721*qBlue(rgb);
		int l = ( std::max ( qRed(rgb), std::max(qGreen(rgb), qBlue(rgb) ) ) +
			std::min ( qRed(rgb), std::min(qGreen(rgb), qBlue(rgb) ) ) ) / 2;
		if ( l > 255 ) {
			l = 255;
		} else if ( l<0 ) {
			l = 0;
		}
		return l;
	}

	/**
	 * Статический метод setLightness () устанавливает яркость.
	 * @param rgb
	 * @param newLightness
	 * @param oldLightness
	 *
	 * Статический метод setLightness () устанавливает яркость пикселя rgb
	 * в значение newLightness. Если был передан параметр oldLightness,
	 * то текущее значение яркости не вычисляется, а используется старое.
	 * Код доверия перегрузки этого метода должен корректно использоваться
	 * наследниками класса.
	 */
	static inline QRgb setLightness ( QRgb rgb, int newLightness ) {
		int oldLightness = lightness (rgb);
		return setLightness(rgb, newLightness, oldLightness);
	}
	static inline QRgb setLightness ( QRgb rgb, int newLightness, int oldLightness ) {
		if ( newLightness > 255 ) newLightness = 255;
		else if ( newLightness < 0 ) newLightness = 0;
		//Trust 0 <= oldLightness <= 255
		int delta = newLightness - oldLightness;
		int r = qRed(rgb) + delta, g = qGreen(rgb) + delta, b = qBlue (rgb) + delta;
		if (r< 0) r =0;
		else if (r>255) r=255;
		if (g< 0) g =0;
		else if (g>255) g=255;
		if (b< 0) b =0;
		else if (b>255) b=255;
		return qRgb (r,g,b);

	}
	/**
	 * @}
	 */

        /**
	 * Метод copy() создает копию объекта.
	 * @todo должен реализовываться наследниками.
	 */
public:
        virtual Filter* copy() const = 0;

};

class Grayscale : public Filter {
public:
        Grayscale (): Filter() {};
        Grayscale ( const Filter& filter): Filter (filter) {}
        explicit Grayscale ( const QRect &area ): Filter(area) {}
        explicit Grayscale ( const Callback& callback ): Filter (callback) {}
        Grayscale ( const QRect& area, const Callback& callback ): Filter (area, callback) {}

        QImage launch ( const QImage& image ) const;

	Grayscale* copy() const;
};

/**
 * @}
 */


#endif //_FILTER_H
