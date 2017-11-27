#include "SimpleFigure.h"

SimpleFigure::~SimpleFigure()
{
	for(Point *p : points)
		delete p;
}

void SimpleFigure::draw()
{
	glPointSize(1.0);
	glColor3f(1.0, 0.0, 0.0);
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

const vector<Point *> &SimpleFigure::getPoints() const
{
	return points;
}

