#ifndef AREA_H
#define AREA_H

#include "Point.h"
#include <vector>
#include <tuple>
using namespace std;

class Area
{
	static tuple<float,float,float> defaultColor;

public:
	Area();
	static void setColor(tuple<float,float,float> newColor);
	virtual void fillColor();
	virtual void clearColor();
	virtual void drawRect(const Point &a, const Point &b, const Point &c, const Point &d); //绘制以x和y为对角线的矩形虚线框，用于MarkDraw

protected:
	vector<Point*> fillPoints;

private:
	tuple<float,float,float> color;
};

#endif // !AREA_H

