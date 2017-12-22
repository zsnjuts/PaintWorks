#include "SimpleFigure.h"
#include <GL/glu.h>
using namespace std;

SimpleFigure::~SimpleFigure()
{
	for(Point *p : points)
		delete p;
}

void SimpleFigure::draw()
{
	glPointSize(2.0);
	glColor3f(0.0, 0.0, 0.0);
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

