#include "Point.h"
#include <GL/glu.h>
#include <iostream>
using namespace std;

Point::Point()
{
}

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point::~Point()
{
}

int Point::getX() const
{
	return x;
}

int Point::getY() const
{
	return y;
}

int Point::distanceTo(const Point &p) const
{
	return abs(this->x - p.x) + abs(this->y - p.y);
}

void Point::draw()
{
	glVertex2i(x, y);
}

//void Point::markDraw()
//{
//}

//void Point::clear()
//{
//}

void Point::setPoint(int x, int y)
{
	this->x = x;
	this->y = y;
}

// 从上到下，从左到右增大
bool Point::operator<(const Point & p) const
{
	return this->y>p.y || (this->y==p.y && this->x<p.x);
}

bool Point::operator==(const Point & p) const
{
	return this->x==p.x && this->y==p.y;
}

ostream & operator<<(ostream & out, const Point & p)
{
	out << '(' << p.getX() << ',' << p.getY() << ')';
	return out;
}

/*
Point Point::operator+(const Point & p) const
{
if(this->getGlY()+this->getGlutY()==p.getGlY()+p.getGlutY())
return Point(GL_COORDINATE,
this->getGlY()+this->getGlutY(), this->getX()+p.getX(), this->getGlY()+p.getGlY());
else
{
cerr << "两点不在同一坐标系下，不能相加！" << endl;
exit(-1);
}
}*/
