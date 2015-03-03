//NTCU TSCC TEAM , 2015.03
#ifndef COLOR3F_H
#define COLOR3F_H

#define BLACK  0
#define RED    1
#define GREEN  2
#define BLUE   3
#define WHITE  99

class color3f
{
	public:
	float r;
	float g;
	float b;
	void assign(const float R, const float G, const float B)
	{
		r = R;
		g = G;
		b = B;
	}
	void assign(const color3f& color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
	}
	void assign(const int color)
	{
		switch(color)
		{
			case WHITE:
			r=1;
			g=1;
			b=1;
			break;

			case BLACK:
			r=0;
			g=0;
			b=0;
			break;

			case RED:
			r=1;
			g=0;
			b=0;
			break;

			case BLUE:
			r=0;
			g=0;
			b=1;
			break;

			case GREEN:
			r=0;
			g=1;
			b=0;
			break;

			default:
			r=0;
			g=0;
			b=0;
		}
	}

	color3f(float R, float G, float B)
		: r(R) , g(G) , b(B)
	{
	}
	color3f(int color)
	{
		assign(color);
	}
	color3f()
	{
		assign(color3f(WHITE));
	}



};
#endif
