#include "Figure.h"
#include <iostream>
using namespace std;

Figure::~Figure()
{
	clear();
}

void Figure::draw()
{
	glPointSize(1.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (auto it : points)
		it->draw();
	glEnd();
	glFlush();
}

void Figure::clear()
{
	for (auto it : points)
		delete it;
	points.erase(points.begin(), points.end());
}

const vector<Point*>& Figure::getPoints() const
{
	return points;
}
