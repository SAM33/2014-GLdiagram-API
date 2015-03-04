//NTCU TSCC TEAM , 2015.03
#ifndef DIAGRAM_H
#define DIAGRAM_H
#include "point2f.h"
#include "line2f.h"
#include "MyGLgraphic.h"
#include "color3f.h"
#include "label.h"
#include <vector>
#include <iostream>
#include <string.h>
#include <stdio.h>
class singlediagram
{
	public:
	std::vector<point2f> points;
	std::string title;
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
	const static int display_amounty = 10;

	void setdisplayscope(int Display_itemamount)
	{
		display_startitem = 0;
		display_itemamount = Display_itemamount;
	}

	singlediagram(int X, int Y, int Width, int Height)
	{
		setbound(X, Y, Width, Height);
		setvaluerange(0,100);
		setdisplayscope(100);
		settitle("singlediagram");
	}

	void settitle(std::string Title)
	{
		title.assign(Title);
	}

	void settitle(const char * Title)
	{
		title.assign(Title);
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
			draw_xaxis();
			draw_yaxis();
			draw_title();
		}
	}

	void draw1()
	{
        setcolor(datacolor);
        drawpolygon(points);
	}

	void draw2()
	{
        float x_shift = (points.at(display_startitem).x - x);
        setcolor(datacolor);
        drawpolygon(points, -1*x_shift, display_startitem, display_itemamount);
        setcolor(axiscolor);
        drawline(x,y,x+width,y);
        drawline(x,y,x,y+height);
	}

	void draw_title()
	{
		float dx = (width/display_itemamount)*4;
		float dy = height/display_amounty;
		label l(x-dx,y+height+dy,std::string(title),LARGE);
		l.draw();
	}

	void draw_xaxis()
	{
        	setcolor(axiscolor);
        	drawline(x,y,x+width,y);
		for(int i=1 ; i<display_itemamount ; i++)
		{
			float x = itemnum2pointx(i);
			float y1 = y+width/50;
			float y2 = y-width/50;
			drawline(x,y1,x,y2);
			float dx = width/display_itemamount/3;
			float dy = height/display_amounty;
			if(i%2==1)
			{
				char c[10];
				memset(c,0x0,10);
				sprintf(c,"%d",i);
				label l(x-dx,y2-dy,std::string(c),SMALL);
				l.draw();
			}
		}
	}

	void draw_yaxis()
	{
        	setcolor(axiscolor);
        	drawline(x,y,x,y+height);
		for(int i=1 ; i<=display_amounty ; i++)
		{
			float x1 = x+height/50;
			float x2 = x-height/50;
			float value = ((maxvalue-minvalue)/display_amounty)*i;
			float y = value2pointy(value);
			drawline(x1,y,x2,y);
			float dx = (width/display_itemamount)*4;
			float dy = height/display_amounty/3;
			char c[10];
			memset(c,0x0,10);
			sprintf(c,"%.1lf",value);
			label l(x2-dx,y-dy,std::string(c),SMALL);
			l.draw();
		}
	}

	private:
	float value2pointy(float value)
	{
		if((maxvalue-minvalue)==0)
			return 0;
		if(value>maxvalue || value<minvalue)
			std::cerr<<"uncorrect value "<<value<<std::endl;

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
