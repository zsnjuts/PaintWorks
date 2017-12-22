#include "SimpleFigure.h"
#include <GL/glu.h>
using namespace std;

tuple<float,float,float> SimpleFigure::defaultColor(0.0, 0.0, 0.0); //初始化填充色为绿色
SimpleFigure::SimpleFigure()
{
	color = make_tuple(-1.0,-1.0,-1.0);
}

SimpleFigure::~SimpleFigure()
{
	for(Point *p : points)
		delete p;
}

void SimpleFigure::setColor(tuple<float, float, float> newColor)
{
	defaultColor = newColor;
}

void SimpleFigure::draw()
{
	if(std::get<0>(color)<0)
		color = defaultColor;

	glPointSize(2.0);
	glColor3f(std::get<0>(color), std::get<1>(color), std::get<2>(color));
//	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (auto it : points)
		it->draw();
	glEnd();
	glFlush();
}

void SimpleFigure::clear()
{
	for (auto it : points)
		delete it;
	points.erase(points.begin(), points.end());
}

bool SimpleFigure::isOn(const Point &p)
{
	for(Point *pt:points)
		if(pt->distanceTo(p)<3)
			return true;
	return false;
}

const vector<Point *> &SimpleFigure::getPoints() const
{
	return points;
}

