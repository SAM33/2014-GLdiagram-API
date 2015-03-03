//NTCU TSCC TEAM , 2015.03
#ifndef LINE2F_H
#define LINE2F_H

#include "point2f.h"
class line2f
{
	public:
	point2f start;
	point2f end;
	line2f(point2f START, point2f END)
	{
		start.assign(START);
		end.assign(END);
	}
	line2f(float X1, float Y1, float X2, float Y2)
	{
		start.assign(X1,Y1);
		end.assign(X2,Y2);
	}
};
#endif
