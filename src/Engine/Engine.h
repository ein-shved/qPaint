#pragma once
#ifndef _CENGINE_H
#define _CENGINE_H

#include <string>
using namespace std;
#include <QImage>
#include <QQueue>
#include "Filter.h"

/** @class Engine
 *
 * Класс Engine, представляет из себя механизм управления фильтрами и 
 * картинками.
 *
 * @property _image
 * @property _filters
 * @property _path
 *
 * Класс Engine, представляет из себя механизм управления фильтрами,
 * которые храняться в очереди _filters. При вызове метода launch,
 * фильтры запускаются по очереди и им передается катринка _image.
 */

class Filter;

class Engine
{
	QImage _image; //картинка
        QQueue<Filter*> _filters;
	QString _path;
public:
	
	/**
	 * Метод load() загружает картинку.
	 * @param in_sPath
	 * 
	 * Метод load() загружает картинку, находящуюся в пути in_sPath и сохраняет ее
	 * в _image.
	 */
	bool load(const QString &in_sPath);

	/**
	 * Метод save () сохраняет картинку.
	 * @param in_sPath
	 * 
	 * Метод save () сохраняет картинку _image в пути in_sPath.
	 */
	bool save(const QString &in_sPath);

	/**
	 * Геттер getImage() возвращает картинку _image.
	 */
        const QImage inline &getImage() const {
		return _image;
	}

	/**
	 * Метод filter() добавляет фильтр.
	 * @param filter
	 * Метод filter() добавляет фильтр filter в очередь _filters.
	 */
	void inline filter ( const Filter &filter) {
                _filters.enqueue ( filter.copy() );
	}

	/**
	 * Метод launch() запускает все фильтры в очереди.
	 * @param filter
	 * 
	 * Если указан параметр filter, метод launch() запускает все фильтры в очереди,
	 * и после - фильтр filter.
	 */
	void launch ();
        void launch ( const Filter &filter);

	/**
	 * Оператор () вызывает метод launch()
	 */
	void operator () ();

	/**
	 * Метод path() возвращает текущее положение в фс.
	 */
	const inline QString &path () const {
		return _path;
	}
};

#endif //_CENGINE_H
