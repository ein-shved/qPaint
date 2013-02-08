#ifndef _SUPPLEMENTARY_H
#define _SUPPLEMENTARY_H

#include "../Filter.h"

class Glass : public Filter {
public:
        Glass (): Filter() {};
        Glass ( const Filter &filter): Filter (filter) {}
        explicit Glass ( const QRect &area ): Filter(area) {}
        explicit Glass ( const Callback &callback ): Filter (callback) {}
        Glass ( const QRect &area, const Callback &callback ): Filter (area, callback) {}

        QImage launch ( const QImage& image ) const;

	Glass* copy() const;
};



#endif //_SUPPLEMENTARY_H