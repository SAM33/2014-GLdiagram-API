//NTCU TSCC TEAM , 2015.03
#ifndef MYGLGRAPHIC_H
#define MYGLGRAPHIC_H

#include "line2f.h"
#include "point2f.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "color3f.h"
#include <vector>

void setcolor(float R, float G, float B);
void setcolor(const color3f& color);
void drawline(const line2f& line);
void drawline(const point2f& start, const point2f& end);
void drawline(float X1, float Y1, float X2, float Y2);
void drawrectangle(float X1, float Y1, float X2, float Y2);
void drawrectangle(const point2f& start, const point2f& end);
void drawpolygon(const std::vector<point2f>& points, float x_shift , int startn, int length);
void drawpolygon(const std::vector<point2f>& points);

#endif
