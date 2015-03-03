//NTCU TSCC TEAM , 2015.03
#ifndef LINE2F_H
#define LINE2F_H

#include "point2f.h"
class line2f
{
	public:
	point2f start;
	point2f end;
	line2f(const point2f& START, const point2f& END)
		: start(START) , end(END)
	{
	}

	line2f(const float X1, const float Y1, const float X2, const float Y2)
	{
		start = point2f(X1,Y1);
		end = point2f(X2,Y2);
	}
};
#endif
