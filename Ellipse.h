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

	Point getCenter() const;
	vector<Point> getMarkPoints() const;
	Point getHandlePoint() const;

	void setEndPoint(const Point &end);
	void setAxes(int rx, int ry); //设置长轴短轴
	void setHandlePointByRef(const Point &ref);

	void translate(const Point &offset);
	void rotate(double angle);
	void scale(double s);

	bool isOn(const Point &p);

	void markDraw(); //绘制除draw以外的标记：矩形框+标记点

private:
	Point begin;
	Point end;
	Point center;
	int rx, ry;
	vector<Point> markPoints; //标记点
	//下面参数为handle相关
	Point handle; //handle点
	const static int h; //handle长度，初始化为30

	void calculatePoints(); //计算各点位置
	void calculateHandle(); //非旋转操作后更新handle
};

#endif // !ELLIPSE_H

