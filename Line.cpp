#include "Line.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <GL/glu.h>
#include <cassert>
using namespace std;

Line::Line()
{
}

Line::Line(const Point &begin, const Point &end)
{
	this->begin = begin;
	this->end = end;
	updateParameters();
	calculatePoints();
	calculateRelatedPoints();
}

Point Line::getBeginPoint() const
{
	return begin;
}

Point Line::getEndPoint() const
{
	return end;
}

Point Line::getDownPoint() const
{
	return *down;
}

Point Line::getUpPoint() const
{
	return *up;
}

Point Line::getCenterPoint() const
{
	return center;
}

Point Line::getHandlePoint() const
{
	return handle;
}

Point Line::intersectWithX(int x) const
{
	assert(begin.getX()!=end.getX());
	double k = (double)(end.getY()-begin.getY()) / (double)(end.getX()-begin.getX());
	return Point(x, int(k*(x-begin.getX()) + begin.getY() + 0.5));
}

Point Line::intersectWithY(int y) const
{
	assert(begin.getY()!=end.getY());
	double m = (double)(end.getX()-begin.getX()) / (double)(end.getY()-begin.getY());
	return Point(int(m*(y-begin.getY()) + begin.getX() + 0.5), y);
}

void Line::setBeginPoint(const Point &p)
{
	clear();
	begin = p;
	updateParameters();
	calculatePoints();
	calculateRelatedPoints();
}

void Line::setEndPoint(const Point &p)
{
	clear();
	end = p;
	updateParameters();
	calculatePoints();
	calculateRelatedPoints();
}

void Line::setLine(const Point &begin, const Point &end)
{
	clear();
	this->begin = begin;
	this->end = end;
	updateParameters();
	calculatePoints();
	calculateRelatedPoints();
}

const int Line::h = 30; //初始化handle长度
void Line::setHandlePointByRef(const Point &ref)
{
	//计算handle(center不变)
	if(center==ref) //参考点与中点重合，不旋转
		return;
	handle.rotateToParallel(center, ref, h);

	//计算begin，end并更新直线
	clear();
	begin.rotateToPerpendicularUp(center, ref, length/2);
	end.rotateToPerpendicularDown(center, ref, length/2);
	updateParameters();
	calculatePoints();
}

void Line::translate(const Point &offset)
{
	clear();
	begin.translate(offset);
	end.translate(offset);
	updateParameters();
	calculatePoints();
	calculateRelatedPoints();
}

void Line::rotate(double angle)
{
	clear();
	Point ctr((begin.getX()+end.getX())/2, (begin.getY()+end.getY())/2);
	begin.rotate(ctr, angle);
	end.rotate(ctr, angle);
	updateParameters();
	calculatePoints();
	calculateRelatedPoints();
}

void Line::scale(double s)
{
	clear();
	Point mid((begin.getX()+end.getX())/2, (begin.getY()+end.getY())/2);
	begin.scale(mid, s, s);
	end.scale(mid, s, s);
	updateParameters();
	calculatePoints();
	calculateRelatedPoints();
}

bool Line::cut(const Point &leftDown, int width, int height)
{
	const int xwmin = leftDown.getX(), xwmax = leftDown.getX()+width;
	const int ywmin = leftDown.getY(), ywmax = leftDown.getY()+height;
	const int x1 = begin.getX(), y1 = begin.getY();
	const int x2 = end.getX(), y2 = end.getY();
	const int dx = x2-x1, dy = y2-y1;
	int p[] = {-dx, dx, -dy, dy}; //指示方向：内->外or外->内
	int q[] = {x1-xwmin, xwmax-x1, y1-ywmin, ywmax-y1}; //指示位置：在内侧or在外侧
	double u1 = 0, u2 = 1; //记录两侧裁剪边界的u值
	for(int i=0;i<4;i++)
	{
		if(p[i]==0) //平行于此边界
		{
			if(q[i]<0) //在此边界的外部，直接丢弃；在内部，则本边界对此直线没有裁剪点，不做更改
				return false;
		}
		else //与此边界的直线有交点，裁剪
		{
			double r = (double)q[i]/(double)p[i];
			if(p[i]<0) //外->内
				u1 = max(u1, r);
			else //内->外
				u2 = min(u2, r);
		}
	}

	if(u1>u2) //裁剪的左侧在右侧的右边，舍弃
		return false;
	else
	{
		setLine(Point(x1+int(u1*dx+0.5), y1+int(u1*dy+0.5)),
				Point(x1+int(u2*dx+0.5), y1+int(u2*dy+0.5)));
		return true;
	}
}

bool Line::isOn(const Point &p)
{
	return (end.getX()-begin.getX())*(p.getY()-begin.getY()) == (p.getX()-begin.getX())*(end.getY()-begin.getY());
}

void Line::markDraw()
{
	begin.markDraw();
	end.markDraw();
	center.centerMarkDraw(); //中点
	handle.handleDraw(center);
}

void Line::plainMarkDraw()
{
	begin.markDraw();
	end.markDraw();
}

void Line::updateParameters()
{
	this->left = begin.getX() <= end.getX() ? &this->begin : &this->end;
	this->right = begin.getX() <= end.getX() ? &this->end : &this->begin;
	this->down = begin.getY() <= end.getY() ? &this->begin : &this->end;
	this->up = begin.getY() <= end.getY() ? &this->end : &this->begin;
}

void Line::calculateRelatedPoints()
{
	//计算长度
	length = begin.distanceTo(end);
	//计算center
	center.setPoint((begin.getX()+end.getX())/2, (begin.getY()+end.getY())/2);
	//计算handle
	handle.setHandlePoint(begin, end, h);
}

void Line::calculatePoints()
{
	int dx = right->getX() - left->getX();
	int dy = right->getY() - left->getY();
	if (((dx^dy) >> 31) == 0) //dx与dy同号，斜率k>=0
	{
		if (dy <= dx) //斜率0<=k<=1
			bresenham01(dx, dy);
		else //斜率k>1
			bresenham1inf(dx, dy);
	}
	else //dx与dy异号，斜率k<0
	{
		if (abs(dy) <= abs(dx)) //斜率-1<=k<0
			bresenham_10(dx, dy);
		else //斜率k<-1
			bresenham_inf_1(dx, dy);
	}
}

// 绘制0<=k<=1的直线
void Line::bresenham01(int dx, int dy)
{
	points.push_back(new Point(left->getX(), left->getY()));
	for (int x = left->getX(), p = 2 * dy - dx, y = left->getY(); x < right->getX(); )
	{
		if (p >= 0)
		{
			points.push_back(new Point(++x, ++y));
			p += 2 * dy - 2 * dx;
		}
		else
		{
			points.push_back(new Point(++x, y));
			p += 2 * dy;
		}
	}
	if (left != &begin) //保证点从begin绘制到end
		reverse(points.begin(), points.end());
}

// 绘制-1<=k<0的直线
void Line::bresenham_10(int dx, int dy)
{
	dy = abs(dy);
	points.push_back(new Point(left->getX(), left->getY()));
	for (int x = left->getX(), p = 2 * dy - dx, y = left->getY(); x < right->getX(); )
	{
		if (p >= 0)
		{
			points.push_back(new Point(++x, --y));
			p += 2 * dy - 2 * dx;
		}
		else
		{
			points.push_back(new Point(++x, y));
			p += 2 * dy;
		}
	}
	if (left != &begin)
		reverse(points.begin(), points.end());
}

// 绘制k>1的直线
void Line::bresenham1inf(int dx, int dy)
{
	points.push_back(new Point(down->getX(), down->getY()));
	for (int y = down->getY(), p = 2 * dx - dy, x = down->getX(); y < up->getY(); )
	{
		if (p >= 0)
		{
			points.push_back(new Point(++x, ++y));
			p += 2 * dx - 2 * dy;
		}
		else
		{
			points.push_back(new Point(x, ++y));
			p += 2 * dx;
		}
	}
	if (down != &begin)
		reverse(points.begin(), points.end());
}

// 绘制k<-1的直线
void Line::bresenham_inf_1(int dx, int dy)
{
	dy = abs(dy);
	points.push_back(new Point(down->getX(), down->getY()));
	for (int y = down->getY(), p = 2 * dx - dy, x = down->getX(); y < up->getY(); )
	{
		if (p >= 0)
		{
			points.push_back(new Point(--x, ++y));
			p += 2 * dx - 2 * dy;
		}
		else
		{
			points.push_back(new Point(x, ++y));
			p += 2 * dx;
		}
	}
	if (down != &begin)
		reverse(points.begin(), points.end());
}
