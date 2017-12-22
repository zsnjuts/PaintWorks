#ifndef SIMPLEFIGURE_H
#define SIMPLEFIGURE_H

#include "Point.h"
#include "Figure.h"
#include <vector>

class SimpleFigure : public Figure
{
	static tuple<float,float,float> defaultColor;

public:
	SimpleFigure();
	~SimpleFigure();
	static void setColor(tuple<float,float,float> newColor);
	virtual void draw();
	virtual void clear();
	virtual bool isOn(const Point &p); //该点是否在轮廓上(调用所有点的距离函数来判断点p是否在本直线上)
	const std::vector<Point*> &getPoints() const;

protected:
	std::vector<Point*> points;

private:
	tuple<float,float,float> color;
};

#endif // SIMPLEFIGURE_H
