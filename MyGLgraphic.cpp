#include "MyGLgraphic.h"

void setcolor(float R, float G, float B)
{
	glColor3f(R,G,B);
}

void setcolor(const color3f& color)
{
	float R = color.r;
	float G = color.g;
	float B = color.b;
	setcolor(R, G, B);
}

void drawline(const line2f& line)
{
	float X1 = line.start.x;
	float Y1 = line.start.y;
	float X2 = line.end.x;
	float Y2 = line.end.y;
	drawline(X1,Y1,X2,Y2);
}

void drawline(const point2f& start, const point2f& end)
{
	float X1 = start.x;
	float Y1 = start.y;
	float X2 = end.x;
	float Y2 = end.y;
	drawline(X1,Y1,X2,Y2);
}

void drawline(float X1, float Y1, float X2, float Y2)
{
	glBegin(GL_LINES);
	glVertex2d(X1, Y1);
	glVertex2d(X2, Y2);
	glEnd();
}

void drawrectangle(float X1, float Y1, float X2, float Y2)
{
	glBegin(GL_LINES);
	glVertex2d(X1, Y1);
	glVertex2d(X1, Y2);
	glVertex2d(X1, Y1);
	glVertex2d(X2, Y1);
	glVertex2d(X2, Y2);
	glVertex2d(X1, Y2);
	glVertex2d(X2, Y2);
	glVertex2d(X2, Y1);
	glEnd();
}

void drawrectangle(const point2f& start, const point2f& end)
{
	float X1 = start.x;
	float Y1 = start.y;
	float X2 = end.x;
	float Y2 = end.y;
	drawrectangle(X1,Y1,X2,Y2);
}

void drawpolygon(const std::vector<point2f>& points, float x_shift , int startn, int length)
{
	point2f startp;
	point2f endp;
	if(points.size()<=1)
		return;
	if(length<=1)
		return;
	for(int i=startn+1; i<startn+length ; i++)
	{
		startp.assign(points.at(i-1).x+x_shift, points.at(i-1).y);
		endp.assign(points.at(i).x+x_shift, points.at(i).y);
		drawline(startp, endp);
	}
}

void drawpolygon(const std::vector<point2f>& points)
{
	point2f startp;
	point2f endp;
	int size=points.size();
	if(size<=1)
		return;
	for(int i=1 ; i<size ; i++)
	{
		startp.assign(points.at(i-1));
		endp.assign(points.at(i));
		drawline(startp, endp);
	}
}
