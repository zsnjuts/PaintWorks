#include "Curve.h"
#include <GL/glu.h>
#include <cmath>

Curve::Curve()
{
}

Curve::Curve(const vector<Point> &vertices)
{
	this->vertices = vertices;
	calculatePoints();
}

Curve::~Curve()
{
}

vector<Point> Curve::getVertices() const
{
	return vertices;
}

void Curve::setVertex(int idx, const Point &p)
{
	if(idx>=vertices.size())
		return;
	clear();
	vertices[idx] = p;
	calculatePoints();
}

void Curve::draw()
{
	SimpleFigure::draw();
}

void Curve::markDraw()
{
	for(Point p:vertices)
		p.markDraw();
	glLineWidth(1.0f); //宽度为1
	glEnable(GL_LINE_STIPPLE); //开启虚线绘制功能
	glLineStipple(1, 0x0f0f); //虚线
	glColor3f(0.0, 0.0, 1.0); //蓝色
	glBegin(GL_LINES);
	for(int i=0;i+1<(int)vertices.size();i++)
	{
		glVertex2i(vertices[i].getX(), vertices[i].getY());
		glVertex2i(vertices[i+1].getX(), vertices[i+1].getY());
	}
	glEnd();
	glFlush();
	glDisable(GL_LINE_STIPPLE); //关闭虚线绘制功能
}

void Curve::clear()
{
	SimpleFigure::clear();
}

void Curve::calculatePoints()
{
	if(vertices.size()<4)
		return;
	//根据vertices中前4个点计算曲线各点
	for(double u=0;u<=1;u+=0.001)
	{
		double a = pow(1-u,3);
		double b = 3*u*pow(1-u,2);
		double c = 3*pow(u,2)*(1-u);
		double d = pow(u,3);
		points.push_back(new Point(a*vertices[0].getX() + b*vertices[1].getX() + c*vertices[2].getX() + d*vertices[3].getX() + 0.5,
								   a*vertices[0].getY() + b*vertices[1].getY() + c*vertices[2].getY() + d*vertices[3].getY() + 0.5));
	}
}

void Curve::translate(const Point &offset)
{
	for(Point &p:vertices)
		p.translate(offset);
	for(Point *p:points)
		p->translate(offset);
}

void Curve::rotate(double angle)
{

}

void Curve::scale(double s)
{

}

bool Curve::isOn(const Point &p)
{
	return SimpleFigure::isOn(p);
}

