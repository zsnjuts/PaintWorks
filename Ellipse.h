#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Point.h"
#include "SimpleFigure.h"

class MyEllipse:public SimpleFigure
{
public:
	MyEllipse();
	MyEllipse(const Point &begin, const Point &end);
	MyEllipse(const Point &center, int rx, int ry);

	void setEndPoint(const Point &end);

private:
	Point begin;
	Point end;
	Point center;
	int rx, ry;

	void calculatePoints(); //计算各点位置
};

#endif // !ELLIPSE_H

