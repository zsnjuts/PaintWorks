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

	Point getCenter() const;
	vector<Point> getMarkPoints() const;
	Point getHandlePoint() const;
	void setRadius(int r);
	void setHandlePointByRef(const Point &ref); //ref(参考点)为当前鼠标位置，只需设置handle点，center点与ref点共线即可，在圆中该函数不改变圆的关键属性

	void translate(const Point &offset);
	void rotate(double angle);
	void scale(double s);

	void draw(); //画轮廓点，若被填充，则也画填充点
	void clear(); //删除轮廓点，若被填充，也删除填充点
	void markDraw(); //绘制除draw以外的标记：矩形框+标记点
	void fillColor(); //填充

private:
	Point center; //圆心
	int radius; //半径
	vector<Point> markPoints; //标记点
	//下面参数为handle相关
	Point handle; //handle点
	const static int h; //handle长度，初始化为30

	void calculatePoints(); //计算轮廓点位置
	void calculateFillPoints(); //计算填充点位置
	void calculateHandle(); //更新handle
};

#endif // !CIRCLE_H
