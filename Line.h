#ifndef LINE_H
#define LINE_H

#include "Point.h"
#include "SimpleFigure.h"

class Line: public SimpleFigure
{
public:
	Line();
	Line(const Point &begin, const Point &end);

	Point getBeginPoint() const;
	Point getEndPoint() const;
	Point getDownPoint() const;
	Point getUpPoint() const;
	Point getCenterPoint() const;
	Point getHandlePoint() const;

	void setBeginPoint(const Point &p);
	void setEndPoint(const Point &p);
	void setLine(const Point &begin, const Point &end);
	void setHandlePointByRef(const Point &ref); //ref(参考点)为当前鼠标位置，只需设置handle点，center点与ref点共线即可,center和length不变

	void translate(const Point &offset); //平移
	void rotate(double angle); //绕中点旋转
	void scale(double s); //以中点为基准进行放缩

	bool cut(const Point &leftDown, int width, int height); //根据矩形窗口裁剪，若不在窗口中则返回false

	void markDraw(); //只负责绘制draw以外的标记，不绘制直线本身

private:
	Point begin;
	Point end;
	Point *left;
	Point *right;
	Point *up;
	Point *down;
	//下面两点只是在交互中会用到，不作为直线的关键信息，在calculatePoints()函数中更新
	Point center; //中点
	Point handle; //handle点
	double length; //直线长度，在旋转中用到
	const static int h; //handle长度

	void updateParameters();
	void calculateRelatedPoints(); //每次非旋转操作之后更新center和handle，以及length
	void calculatePoints(); //根据begin和end计算直线所有点
	void bresenham01(int dx, int dy);
	void bresenham_10(int dx, int dy);
	void bresenham1inf(int dx, int dy);
	void bresenham_inf_1(int dx, int dy);
};

#endif // !LINE_H

