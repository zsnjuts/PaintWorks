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
	Point getCenter() const;
	Point getHandle() const;
	void setVertex(int idx, const Point &p); //设置索引为idx的顶点位置
	void setHandlePointByRef(const Point &ref); //ref(参考点)为当前鼠标位置，只需设置handle点，center点与ref点共线即可

	void translate(const Point &offset);
	void rotate(double angle);
	void scale(double s);

	bool isOn(const Point &p);
	bool isOnPlain(const Point &p);

	void draw();
	void markDraw();
	void clear(); //只清除曲线上的点，不清除控制点

private:
	vector<Point> vertices; //4个控制点:begin,*,*,end
	Point center; //中心，重新生成曲线时由calculatePoints()计算得到
	Point handle; //非旋转之后由calculatePoints()之后得到，旋转时直接计算
	const static int h; //handle长度，初始化为30

	void calculatePoints(); //根据控制点计算曲线上各点和center
	void calculateCenter(); //根据控制点计算center
};

#endif // CURVE_H
