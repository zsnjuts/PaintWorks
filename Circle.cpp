#include "Circle.h"
#include <GL/glu.h>
#include <algorithm>

Circle::Circle()
{
}

Circle::Circle(Point center, int radius)
{
	this->center = center;
	this->radius = radius;
	calculatePoints();
}

Circle::~Circle()
{
	for(Point *p : fillPoints)
		delete p;
	for(Point *p : points)
		delete p;
}

void Circle::draw()
{
	SimpleFigure::draw();
	Area::fillColor();
}

void Circle::clear()
{
	SimpleFigure::clear();
	Area::clearColor();
}

Point Circle::getCenter()
{
	return center;
}

void Circle::setRadius(int r)
{
	bool isFilled = !fillPoints.empty();
	clear();
	this->radius = r;
	calculatePoints();
	if(isFilled)
		fillColor();
}

void Circle::fillColor()
{
	if (radius <= 0 || !fillPoints.empty())
		return;

	int minY = center.getY() - radius;
	int maxY = center.getY() + radius;
	vector<vector<Point*>> scanLines(maxY - minY + 1);
	for (Point *p : points)
		scanLines[p->getY() - minY].push_back(p);

	vector<vector<pair<Point*, Point*>>> outline(maxY - minY + 1);//保留了最上一行和最下一行，但均为空
	for (vector<vector<Point*>>::iterator it = scanLines.begin(); it+1 != scanLines.end(); it++)
	{
		//注：此方法有一点不适合多边形，即多边形有时需要顶点冗余来保持一些在内部的区间仍然被绘制，但这里被统一过滤掉了
		//因为这里有可能会有无用的冗余，所以直接滤掉，多边形那里应该保留相同的点，去掉距离小于1的点
		sort(it->begin(), it->end(), [](Point *x, Point *y)->bool {return *x < *y; });
		for (vector<Point*>::iterator i = it->begin(); i != it->end() && i + 1 != it->end(); i++)
			if ((*(i + 1))->getX() - (*i)->getX() > 1
				&& outline[it-scanLines.begin()].size()%2==0) //只保留内部的，空隙较大的点
				outline[it-scanLines.begin()].push_back(make_pair(*i, *(i + 1)));
	}

	for (vector<pair<Point*, Point*> > line : outline)
		for (pair<Point*, Point*> pr : line)
			for (int i = pr.first->getX() + 1; i < pr.second->getX(); i++)
				fillPoints.push_back(new Point(i, pr.first->getY()));
}

void Circle::calculatePoints()
{
	if (radius <= 0)
		return;
	points.push_back(new Point(center.getX(), center.getY() + radius)); //最上
	points.push_back(new Point(center.getX() + radius, center.getY())); //最右
	points.push_back(new Point(center.getX(), center.getY() - radius)); //最下
	points.push_back(new Point(center.getX() - radius, center.getY())); //最左
	for (int x = 0, y = radius, p = 5 - 4 * radius; x < y;)
	{
		x++;
		if (p < 0)
			p += 4 * (2 * x + 3);
		else
		{
			y--;
			p += 4 * (2 * x - 2 * y + 3);
		}
		points.push_back(new Point(center.getX() + x, center.getY() + y)); //第一象限y=x上方(顺时针0°)
		points.push_back(new Point(center.getX() + y, center.getY() - x)); //第四象限y=-x上方(顺时针90°)
		points.push_back(new Point(center.getX() - x, center.getY() - y)); //第三象限y=x下方(顺时针180°)
		points.push_back(new Point(center.getX() - y, center.getY() + x)); //第二象限y=-x下方(顺时针270°)
		if (x < y) //避免在y=x和y=-x上的点重复出现
		{
			points.push_back(new Point(center.getX() + y, center.getY() + x)); //第一象限y=x下方(关于y=x对称后顺时针0°)
			points.push_back(new Point(center.getX() + x, center.getY() - y)); //第四象限y=-x下方(关于y=x对称后顺时针90°)
			points.push_back(new Point(center.getX() - y, center.getY() - x)); //第三象限y=x上方(关于y=x对称后顺时针180°)
			points.push_back(new Point(center.getX() - x, center.getY() + y)); //第二象限y=-x上方(关于y=x对称后顺时针270°)
		}
	}
}
