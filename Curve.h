#ifndef CURVE_H
#define CURVE_H

#include "Point.h"
#include "SimpleFigure.h"

class Curve: public SimpleFigure
{
public:
	Curve();
	Curve(const vector<Point> &vertices);
	~Curve();

	vector<Point> getVertices() const;
	void setVertex(int idx, const Point &p); //设置索引为idx的顶点位置

	void translate(const Point &offset);
	void rotate(double angle);
	void scale(double s);

	bool isOn(const Point &p);

	void draw();
	void markDraw();
	void clear();

private:
	vector<Point> vertices; //4个控制点:begin,*,*,end

	//界面相关，在calculateHandle()函数中更新
	void calculatePoints(); //根据控制点计算曲线上各点
};

#endif // CURVE_H
