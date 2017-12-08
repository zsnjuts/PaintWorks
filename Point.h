#ifndef POINT_H
#define POINT_H

#include <tuple>
#include <iostream>
using namespace std;

class Point
{
public:
	Point();
	Point(int x, int y);
	~Point();

	int getX() const;
	int getY() const;
	double distanceTo(const Point &p) const;

	void draw(); //需要结合glBegin()和glEnd()使用
	void markDraw(); //被选中的状态
	void centerMarkDraw(); //中心点标记
	void handleDraw(const Point &p); //标记+与另一个点的连线
//	void clear(); //暂无用处

	void setPoint(int x, int y);
	void translate(const Point &offset);
	void rotate(const Point &ctr, double angle); //ctr为旋转中心，angle为度，不是弧度
	void scale(const Point &base, double sx, double sy); //base为基准点，sx和sy分别为两个方向的缩放系数，0-1表示缩小，>1表示放大

	//有参考点的旋转，this与base固定距离为dist，调用者要保证旋转中dist不变，精度损失就可以比较小，返回true表示正常旋转，false表示旋转出错，则不旋转
	//注：使用rotateToParallel()的调用者要提前处理好base与ref重合的情况，否则出错
	bool rotateToParallel(const Point &base, const Point &ref, double dist); //绕base旋转至与base,ref共线
	//注：使用rotateToPerpendicular()族函数的调用者要提前处理好ref.x=base.y的情况，否则出错
	bool rotateToPerpendicularLeft(const Point &base, const Point &ref, double dist); //绕base旋转至(base,this)垂直于(base,ref)，左侧的垂直点
	bool rotateToPerpendicularRight(const Point &base, const Point &ref, double dist); //绕base旋转至(base,this)垂直于(base,ref)，右侧的垂直点

	bool operator<(const Point &p) const;
	bool operator==(const Point &p) const;
	Point operator-(const Point &p) const;
	friend ostream& operator<<(ostream &out, const Point &p); //输出(x,y)坐标
	//Point operator+(const Point &p) const;

private:
	int x; //gl与glut横坐标相同
	int y; //glY,以gl坐标系为准，y轴原点在左下角
};

#endif // !POINT_H
