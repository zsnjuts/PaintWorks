#include "Ellipse.h"
#include <cassert>
#include <cmath>

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
	calculateHandle();
}

MyEllipse::MyEllipse(const Point & center, int rx, int ry)
{
	this->center = center;
	this->rx = rx;
	this->ry = ry;
	calculatePoints();
	calculateHandle();
}

void MyEllipse::markDraw()
{
	markPoints.erase(markPoints.begin(), markPoints.end());
	markPoints.push_back(Point(center.getX()-rx, center.getY()-ry));
	markPoints.push_back(Point(center.getX()-rx, center.getY()+ry));
	markPoints.push_back(Point(center.getX()+rx, center.getY()+ry));
	markPoints.push_back(Point(center.getX()+rx, center.getY()-ry));
	Area::drawRect(markPoints[0], markPoints[1], markPoints[2], markPoints[3]);
	for(Point p:markPoints)
		p.markDraw();
	center.centerMarkDraw();
	handle.handleDraw(center);
}

Point MyEllipse::getCenter() const
{
	return center;
}

vector<Point> MyEllipse::getMarkPoints() const
{
	return markPoints;
}

Point MyEllipse::getHandlePoint() const
{
	return handle;
}

void MyEllipse::setEndPoint(const Point &end)
{
	clear();
	this->end = end;
	rx = abs(end.getX() - begin.getX())/2;
	ry = abs(end.getY() - begin.getY())/2;
	center.setPoint((begin.getX() + end.getX())/2, (begin.getY()+end.getY())/2);
	calculatePoints();
	calculateHandle();
}

void MyEllipse::setAxes(int rx, int ry)
{
	clear();
	this->begin.setPoint(center.getX()-rx, center.getY()-ry); //begin为左下角
	this->end.setPoint(center.getX()+rx, center.getY()+ry); //end为右上角
	this->rx = rx;
	this->ry = ry;
	calculatePoints();
	calculateHandle();
}

void MyEllipse::setHandlePointByRef(const Point &ref)
{
	if(ref.getX()==center.getX() || ref.getY()==center.getY()) //若(center,ref)水平或垂直，则旋转90度
		setAxes(ry, rx);
	handle.rotateToParallel(center, ref, h);
}

void MyEllipse::translate(const Point &offset)
{
	clear();
	center.translate(offset);
	begin.translate(offset);
	end.translate(offset);
	calculatePoints();
	calculateHandle();
}

void MyEllipse::rotate(double angle)
{
	int tmp = abs((int)angle)%180;
	if(tmp>=0 && tmp<90) //abs(angle%180)在[0,90)区间，则不变
		return;
	else //abs(angle%180)在[90,180)区间，旋转90度
		setAxes(ry, rx);
}

void MyEllipse::scale(double s)
{
	setAxes(rx*s, ry*s);
}

bool MyEllipse::isOn(const Point &p)
{
	if(SimpleFigure::isOn(p))
		return true;
	if(!fillPoints.empty())
	{
		for(Point *pt:fillPoints)
			if(*pt==p)
				return true;
	}
	return false;
}

void MyEllipse::calculatePoints()
{
	if (rx <= 0 || ry <= 0) //防止计算未初始化的椭圆
		return;
	
	/* 第一象限上面的区域(|切线斜率|<=1) */
	long long rx = this->rx, ry = this->ry; //将rx，ry转为long long防止溢出
	long long x = 0, y = ry, p = 4 * ry*ry - 4 * rx*rx*ry + rx*rx; //x，y均使用long long以防溢出
	while (ry*ry*x < rx*rx*y)
	{
		if (p < 0)
		{
			p += 4 * (2 * ry*ry*x + 3 * ry*ry);
			x++;
		}
		else
		{
			p += 4 * (2 * ry*ry*x - 2 * rx*rx*y + 2 * rx*rx + 3 * ry*ry);
			y--;
			x++;
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
		if (p <= 0)
		{
			p += 4 * (2 * ry*ry*x - 2 * rx*rx*y + 2 * ry*ry + 3 * rx*rx);
			x++;
			y--;
		}
		else
		{
			p += 4 * (-2 * rx*rx*y + 3 * rx*rx);
			y--;
		}

		points.push_back(new Point(center.getX() + x, center.getY() + y)); //第一象限
		points.push_back(new Point(center.getX() - x, center.getY() + y)); //第二象限
		points.push_back(new Point(center.getX() - x, center.getY() - y)); //第三象限
		points.push_back(new Point(center.getX() + x, center.getY() - y)); //第四象限
	}
}

const int MyEllipse::h = 30; //初始化handle长度
void MyEllipse::calculateHandle()
{
	if(rx<=0 || ry<=0)
	{
		handle.setPoint(center.getX(), center.getY()+h);
		return;
	}
	double tmp = sqrt(rx*rx+ry*ry);
	handle.setPoint(center.getX()+int(h*rx/tmp+0.5), center.getY()+int(h*ry/tmp+0.5));
}
