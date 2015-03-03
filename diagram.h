//NTCU TSCC TEAM , 2015.03
#ifndef DIAGRAM_H
#define DIAGRAM_H
#include "point2f.h"
#include "line2f.h"
#include "MyGLgraphic.h"
#include "color3f.h"
#include <vector>

class singlediagram
{
	public:
	std::vector<point2f> points;
	float maxvalue;
	float minvalue;
	int width;		                   //width of singlediagram which display in user intrtface windows
	int height;                        //height of singlediagram which display in user intrtface windows
	int x;			                       //location-x of singlediagram (base on x-axis,y-axis cross point)
	int y;                                  //location-y of singlediagram (base on x-axis,y-axis cross point)
	int display_itemamount; //how many items in values should display on this singlediagram
	int display_startitem;      //which value is the first item display on left of singlediagram
	color3f axiscolor;
	color3f datacolor;

	void setdisplayscope(int Display_itemamount)
	{
		display_startitem = 0;
		display_itemamount = Display_itemamount;
	}

	singlediagram(int X, int Y, int Width, int Height, float Minvalue, float Maxvalue)
	{
		singlediagram(X, Y, Width, Height);
		setvaluerange(Minvalue, Maxvalue);
	}

	singlediagram(int X, int Y, int Width, int Height)
	{
		setbound(X, Y, Width, Height);
		setvaluerange(0,100);
		setdisplayscope(10);
	}

	void setbound(int X, int Y, int Width, int Height)
	{
		x = X;
		y = Y;
		width = Width;
		height = Height;
	}

	void setvaluerange(float Minvalue, float Maxvalue)
	{
		maxvalue = Maxvalue;
		minvalue = Minvalue;
	}

	void setdatacolor(color3f Color)
	{
		datacolor.assign(Color);
	}

	void setaxiscolor(color3f Color)
	{
		axiscolor.assign(Color);
	}

	void addvalue(float value)
	{
		float newx,newy;
		point2f newpoint;
		int size=points.size();
		newx=itemnum2pointx(size);
		newy=value2pointy(value);
		newpoint.assign(newx, newy);
		points.push_back(newpoint);
		if(size>display_itemamount)
		{
            display_startitem++;
		}
	}

	void addvalues(float values[],int size)
	{
		for(int i=0 ; i<size ; i++)
			addvalue(values[i]);
	}

	void draw()
	{
		if(width!=0 && height!=0)
		{
            if(points.size()<=display_itemamount)
                draw1();
            else
                draw2();
		}
	}

	void draw1()
	{
        MyGLgraphic::setcolor(datacolor);
        MyGLgraphic::drawpolygon(points);
        MyGLgraphic::setcolor(axiscolor);
        MyGLgraphic::drawline(x,y,x+width,y);
        MyGLgraphic::drawline(x,y,x,y+height);
	}

	void draw2()
	{
        float x_shift = (points.at(display_startitem).x - x);
        MyGLgraphic::setcolor(datacolor);
        MyGLgraphic::drawpolygon(points, -1*x_shift, display_startitem, display_itemamount);
        MyGLgraphic::setcolor(axiscolor);
        MyGLgraphic::drawline(x,y,x+width,y);
        MyGLgraphic::drawline(x,y,x,y+height);
	}

	private:
	float value2pointy(float value)
	{
		if((maxvalue-minvalue)==0)
			return 0;
		float r = (value-minvalue)/(maxvalue-minvalue);
		float ans =  y+(height)*r;
		return ans;
	}
	float itemnum2pointx(int itemnum)
	{
		if((display_itemamount-1)<=0)
			return 0;
		float d = ((float)width/(float)(display_itemamount-1))*(float)itemnum;
		float ans = x+d;
		return ans;
	}

};

#endif
