#include "Area.h"
#include <GL/glu.h>
#include <vector>
#include <iostream>
#include <algorithm>

tuple<float,float,float> Area::defaultColor(0.0, 1.0, 0.0); //初始化填充色为绿色
Area::Area()
{
	color = make_tuple(-1.0,-1.0,-1.0);
}

void Area::setColor(tuple<float, float, float> newColor)
{
	defaultColor = newColor;
}

void Area::fillColor()
{
	if(fillPoints.empty())
		return;
	if(std::get<0>(color)<0)
		color = defaultColor;

	glPointSize(1.0);
	glColor3f(std::get<0>(color), std::get<1>(color), std::get<2>(color));
//	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (auto it : fillPoints)
		it->draw();
	glEnd();
	glFlush();
}

void Area::clearColor()
{
	for(Point *p : fillPoints)
		delete p;
	fillPoints.erase(fillPoints.begin(), fillPoints.end());
}

void Area::drawRect(const Point &a, const Point &b, const Point &c, const Point &d)
{
	glLineWidth(1.0f); //宽度为1
	glEnable(GL_LINE_STIPPLE); //开启虚线绘制功能
	glLineStipple(1, 0x0f0f); //虚线
	glColor3f(0.0, 0.0, 1.0); //蓝色
	glBegin(GL_LINE_LOOP);
	glVertex2i(a.getX(), a.getY());
	glVertex2i(b.getX(), b.getY());
	glVertex2i(c.getX(), c.getY());
	glVertex2i(d.getX(), d.getY());
	glEnd();
	glFlush();
	glDisable(GL_LINE_STIPPLE); //关闭虚线绘制功能
}
