#include "Area.h"
#include <GL/glu.h>
#include <vector>
#include <iostream>
#include <algorithm>

void Area::fillColor()
{
	if(fillPoints.empty())
		return;

	glPointSize(1.0);
	glColor3f(0.0, 0.0, 1.0);
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
