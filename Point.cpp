#include "Point.h"
#include <cmath>
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
	//return abs(this->x - p.x) + abs(this->y - p.y);
	return sqrt((this->x - p.x)*(this->x - p.x) + (this->y - p.y)*(this->y - p.y) + 0.5); //+0.5用于四舍五入
}

void Point::draw()
{
	glVertex2i(x, y);
}

void Point::markDraw()
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	int n = 100; //绘制100个点
	GLfloat R = 5.0f; //圆的半径
	GLfloat pi = 3.1415926536f;
	for(int i=0;i<n;i++)
		glVertex2f(x+R*cos(2*pi/n*i), y+R*sin(2*pi/n*i));
	glEnd();
	glFlush();
}

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
