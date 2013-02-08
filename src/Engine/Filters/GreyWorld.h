#ifndef _GREY_WORLD_H
#define _GREY_WORLD_H

#include "../Filter.h"


class GreyWorld : public Filter {
public:
	GreyWorld (): Filter() {};
        GreyWorld ( const Filter& filter): Filter (filter) {}
        explicit GreyWorld ( const QRect &area ): Filter(area) {}
        explicit GreyWorld ( const Callback& callback ): Filter (callback) {}
        GreyWorld ( const QRect& area, const Callback& callback ): Filter (area, callback) {}

private:
	struct GreyInfo {
		int R,G,B;
		bool inline balance () {
			return (R == G) && (R == B);
		}
		int inline avg () {
			return (R+G+B)/3;
		}
	};
	GreyInfo readGrey ( const QImage& in_Image, const QRect& area = QRect(),
				    int in_percentPart=1, int in_percentStart=0 ) const;
public:

        QImage launch ( const QImage& image ) const;

	GreyWorld* copy() const;
};

#endif //_GREY_WORLD_H