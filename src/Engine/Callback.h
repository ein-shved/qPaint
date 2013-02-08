#ifndef _CALLBACK_H
#define _CALLBACK_H

#include <QMutex>
#include <cstdlib>
#include <iostream>

/** @class Callback
 *
 * Класс Callback, представляет из себя механизм обратной связи
 * фильтра с оболочкой, для передачи информации о текущем
 * состоянии выполнения.
 *
 * @typedef PCALLBACK
 * @param percent
 * @param extra
 *
 * @property _callback
 * @property _extra
 *
 * _callback - указатель, на функцию, которой будет передаваться
 * информация о состоянии выполнения percent в процентах, и
 * дополнительная информация - extra.
 */

#ifndef NULL
#define NULL 0
#endif //NULL


typedef void (*PCALLBACK)(unsigned int percent, void *extra);

class Callback {

private:
	PCALLBACK m_funcCallback;
	void *m_pExtra;

public:
	/**
	 * Конструкторы:
	 *
	 * По у молчанию
	 * устанавливает _callback и _extra в NULL
	 *
	 * Преобразования
	 * @param callback
	 * копирует указатель callback в _callback,
	 * _extra = NULL
	 *
	 * @param callback
	 * @param extra
	 * копирует указатель callback в _callback,
	 * указатель extra в _extra
	 */
	Callback ( PCALLBACK in_funcCallback = NULL, void *in_pExtra = NULL);

	/**
	 * Конструктор копирования
	 * @param callback
	 */
	Callback ( const Callback &callback );

	/**
	 * Операция () вызывает _callback.
	 *
	 * @param percent
	 *
	 * Операция () вызывает _callback, если указатель не равен NULL,
	 * передает в качестве параметров percent и _extra.
	 */
	void inline operator () ( unsigned int percent ) const {
		if ( m_funcCallback )
		/* return */ m_funcCallback ( percent, m_pExtra );
	}

	/**
	 * Сеттер setExtra() для поля _extra.
	 * @param extra
	 */
	void inline setExtra ( void* in_pExtra) {
		m_pExtra = in_pExtra;
	}

	/**
	 * Операция присваивания
	 * @param callback
	 */
        Callback& operator = ( const Callback &callback );
};
#endif //_CALLBACK_H
