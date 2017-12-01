#include "Line.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <GL/glu.h>
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

void Line::setBeginPoint(const Point &p)
{
	clear();
	begin = p;
	updateParameters();
	calculatePoints();
}

void Line::setEndPoint(const Point &p)
{
	clear();
	end = p;
	updateParameters();
	calculatePoints();
}

void Line::setLine(const Point &begin, const Point &end)
{
	clear();
	this->begin = begin;
	this->end = end;
	updateParameters();
	calculatePoints();
}

void Line::markDraw()
{
	begin.markDraw();
	end.markDraw();
}

void Line::translate(const Point &offset)
{
	clear();
	begin.translate(offset);
	end.translate(offset);
	updateParameters();
	calculatePoints();
}

void Line::rotate(double angle)
{
	clear();
	Point ctr((begin.getX()+end.getX())/2, (begin.getY()+end.getY())/2);
	begin.rotate(ctr, angle);
	end.rotate(ctr, angle);
	updateParameters();
	calculatePoints();
}

void Line::updateParameters()
{
	this->left = begin.getX() <= end.getX() ? &this->begin : &this->end;
	this->right = begin.getX() <= end.getX() ? &this->end : &this->begin;
	this->down = begin.getY() <= end.getY() ? &this->begin : &this->end;
	this->up = begin.getY() <= end.getY() ? &this->end : &this->begin;
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
