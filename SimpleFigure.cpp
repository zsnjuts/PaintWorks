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

const vector<Point *> &SimpleFigure::getPoints() const
{
	return points;
}

