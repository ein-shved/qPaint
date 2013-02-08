#ifndef _HYSTOGRAM_H
#define _HYSTOGRAM_H

#include "../Filter.h"
#include <QVector>

/** @class Hystogram @{
 * Класс Hystogram должен наследоваться фильтрами, которые работают с
 * гистограмами. Этот базовый класс реализует вычисление гистограммы со
 * значениями, необходимыми фильтру наследнику. Необходимые значения задаются
 * методом getInterestValue(). При вычислении гистограммы, класс использует
 * сallback с указаной частью и начальным процентным значением.
 *
 * Класс Hystogram не реализует метод launch.
 */

class Hystogram : public Filter {
public:
	Hystogram() {};
        Hystogram( const Filter &filter): Filter (filter) {}
        explicit Hystogram( const QRect &area ): Filter(area) {}
        explicit Hystogram( const Callback &callback ): Filter (callback) {}
        Hystogram ( const QRect &area, const Callback &callback ): Filter (area, callback) {}

protected:
	struct HystogramInfo {
		QVector<uint> hystogram;
		int min;
		int max;
		HystogramInfo() : hystogram(256,0), min(0), max(0) {}
	};
	HystogramInfo readHystogram (const QImage &in_Image, const QRect &in_Area, int extra,
				     int in_percentPart, int in_percentStart ) const;
	virtual int getInterestValue (QRgb in_RGB, int extra) const =0;

public:
	virtual QImage launch ( const QImage& in_Image ) const =0;

	Hystogram* copy() const =0;
};

class HystogramLinear : public Hystogram {
public:
	HystogramLinear(): Hystogram() {};
	HystogramLinear( const Filter &filter): Hystogram(filter) {}
	explicit HystogramLinear ( const QRect &area ): Hystogram(area) {}
	explicit HystogramLinear ( const Callback &callback ): Hystogram(callback) {}
	HystogramLinear ( const QRect &area, const Callback &callback ): Hystogram(area, callback) {}

	int getInterestValue (QRgb in_RGB, int) const;
	virtual QImage launch ( const QImage &in_Image ) const;

	Hystogram* copy() const;
};
class HystogramPerChennel : public Hystogram {
public:
	HystogramPerChennel(): Hystogram() {};
	HystogramPerChennel( const Filter &filter): Hystogram(filter) {}
	explicit HystogramPerChennel ( const QRect &area ): Hystogram(area) {}
	explicit HystogramPerChennel ( const Callback &callback ): Hystogram(callback) {}
	HystogramPerChennel ( const QRect &area, const Callback &callback ): Hystogram(area, callback) {}

private:
	enum ChennelState { red, green, blue};
public:
	int getInterestValue (QRgb in_RGB, int chennel) const;
	virtual QImage launch ( const QImage &in_Image ) const;

	Hystogram* copy() const;
};
/**
 * @}
 */
#endif //_HYSTOGRAM_H
