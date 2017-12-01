#ifndef CIRCLE_H
#define CIRCLE_H

#include "Area.h"
#include "Point.h"
#include "SimpleFigure.h"
#include <vector>
using namespace std;

class Circle: public SimpleFigure, public Area
{
public:
	Circle();
	Circle(Point center, int radius);
	~Circle();

	Point getCenter();
	vector<Point> getMarkPoints();
	void setRadius(int r);

	void translate(const Point &offset);

	void draw(); //画轮廓点，若被填充，则也画填充点
	void clear(); //删除轮廓点，若被填充，也删除填充点
	void markDraw(); //绘制除draw以外的标记：矩形框+标记点
	void fillColor(); //填充

private:
	Point center; //圆心
	int radius; //半径
	vector<Point> markPoints; //标记点

	void calculatePoints(); //计算轮廓点位置
	void calculateFillPoints(); //计算填充点位置
};

#endif // !CIRCLE_H
