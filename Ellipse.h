#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Area.h"
#include "Point.h"
#include "SimpleFigure.h"

class MyEllipse:public SimpleFigure, public Area
{
public:
	MyEllipse();
	MyEllipse(const Point &begin, const Point &end);
	MyEllipse(const Point &center, int rx, int ry);

	Point getCenter();
	vector<Point> getMarkPoints();

	void setEndPoint(const Point &end);
	void setAxes(int rx, int ry); //设置长轴短轴

	void translate(const Point &offset);
	void rotate(double angle);
	void scale(double s);

	void markDraw(); //绘制除draw以外的标记：矩形框+标记点

private:
	Point begin;
	Point end;
	Point center;
	int rx, ry;
	vector<Point> markPoints; //标记点

	void calculatePoints(); //计算各点位置
};

#endif // !ELLIPSE_H

