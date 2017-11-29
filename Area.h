#ifndef AREA_H
#define AREA_H

#include "Point.h"
#include <vector>
using namespace std;

class Area
{
public:
	virtual void fillColor();
	virtual void clearColor();
	virtual void drawRect(const Point &a, const Point &b, const Point &c, const Point &d); //绘制以x和y为对角线的矩形虚线框，用于MarkDraw

protected:
	vector<Point*> fillPoints;
};

#endif // !AREA_H

