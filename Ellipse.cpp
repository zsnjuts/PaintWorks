#include "Ellipse.h"

MyEllipse::MyEllipse()
{
	this->rx = this->ry = -1;
}

MyEllipse::MyEllipse(const Point & begin, const Point & end)
{
	this->begin = begin;
	this->end = end;
	rx = abs(end.getX() - begin.getX()) / 2;
	ry = abs(end.getY() - end.getY()) / 2;
	center.setPoint((begin.getX() + end.getX()) / 2, (begin.getY() + end.getY()) / 2);
	calculatePoints();
}

MyEllipse::MyEllipse(const Point & center, int rx, int ry)
{
	this->center = center;
	this->rx = rx;
	this->ry = ry;
	calculatePoints();
}

void MyEllipse::setEndPoint(const Point &end)
{
	clear();
	this->end = end;
	rx = abs(end.getX() - begin.getX())/2;
	ry = abs(end.getY() - begin.getY())/2;
	center.setPoint((begin.getX() + end.getX())/2, (begin.getY()+end.getY())/2);
	calculatePoints();
}

void MyEllipse::calculatePoints()
{
	if (rx <= 0 || ry <= 0) //防止计算未初始化的椭圆
		return;
	
	/* 上下两个顶点 */
	points.push_back(new Point(center.getX(), center.getY() + ry)); //上
	points.push_back(new Point(center.getX(), center.getY() - ry)); //下
	
	/* 第一象限上面的区域(|切线斜率|<=1) */
	long long x = 0, y = ry, p = 4 * ry*ry - 4 * rx*rx*ry + rx*rx;
	while (ry*ry*x < rx*rx*y)
	{
		x++;
		if (p < 0)
			p += 4 * (2 * ry*ry*x + 3 * ry*ry);
		else
		{
			y--;
			p += 4 * (2 * ry*ry*x - 2 * rx*rx*y + 2 * rx*rx + 3 * ry*ry);
		}
		points.push_back(new Point(center.getX() + x, center.getY() + y)); //第一象限
		points.push_back(new Point(center.getX() - x, center.getY() + y)); //第二象限
		points.push_back(new Point(center.getX() - x, center.getY() - y)); //第三象限
		points.push_back(new Point(center.getX() + x, center.getY() - y)); //第四象限
	}
	
	/* 第一象限下面的区域(|切线斜率|>1)，包括左右两端顶点 */
	p = ry*ry*(2 * x + 1)*(2 * x + 1) + 4 * rx*rx*(y - 1)*(y - 1) - 4 * rx*rx*ry*ry;
	while (y >= 0)
	{
		y--;
		if (p <= 0)
		{
			x++;
			p += 4 * (2 * ry*ry*x - 2 * rx*rx*y + 2 * ry*ry + 3 * rx*rx);
		}
		else
			p += 4 * (-2 * rx*rx*y + 3 * rx*rx);
			
		points.push_back(new Point(center.getX() + x, center.getY() + y)); //第一象限
		points.push_back(new Point(center.getX() - x, center.getY() + y)); //第二象限
		points.push_back(new Point(center.getX() - x, center.getY() - y)); //第三象限
		points.push_back(new Point(center.getX() + x, center.getY() - y)); //第四象限
	}
}
