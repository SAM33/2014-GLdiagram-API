//NTCU TSCC TEAM , 2015.03
#ifndef LABEL_H
#define LABEL_H
#define SMALL 0
#define MIDDLE 1
#define LARGE 2
#include "point2f.h"
#include "MyGLgraphic.h"
#include "color3f.h"
#include <string>
#include <iostream>
class label
{
	public:
	std::string text;
	float x;
	float y; 
	int size;
	
	label(float x, float y, std::string Text , int Size)
	{
		setlocate(x,y);
		setsize(Size);
		settext(Text);
	}

	void setlocate(float X, float Y)
	{
		x = X;
		y = Y;
	}

	void settext(std::string Text)
	{
		text.assign(Text);
	}

	void settext(char *Text)
	{
		text.assign(Text);
	}

	void setsize(int Size)
	{
		size = Size;
	}

	void draw()
	{
		glRasterPos2f(x, y);

		switch(size)
		{
			case SMALL:
    			glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char *)text.c_str());
			break;

			case MIDDLE:
    			glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char *)text.c_str());
			break;			

			case LARGE:
    			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)text.c_str());
			break;

			default:
			glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char *)text.c_str());			
		}
	}

};

#endif
