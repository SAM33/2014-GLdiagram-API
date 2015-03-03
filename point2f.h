//NTCU TSCC TEAM , 2015.03
#ifndef  POINT2F_H
#define POINT2F_H
class point2f
{
	public:
	float x;
	float y;
	point2f()
	{
		x = 0;
		y = 0;
	}

	point2f(const float X,const  float Y)
		: x(X) , y(Y)
	{
	}

	void assign(const point2f& newpoint2f)
	{
		x = newpoint2f.x;
		y = newpoint2f.y;
	}

	void assign(const float X, const float Y)
	{
		x = X;
		y = Y;
	}
};
#endif
