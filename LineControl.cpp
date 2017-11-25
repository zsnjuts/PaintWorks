#include "LineControl.h"

LineControl::LineControl()
{
	curLine = NULL;
}

void LineControl::onMousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::LeftButton)
	{
		curLine = new Line(Point(event->x(), height-event->y()), Point(event->x(), height-event->y()));
		lines.push_back(curLine);
	}
}

void LineControl::onMouseMoveEvent(QMouseEvent *event)
{
	if (curLine == NULL)
		return;
	curLine->setEndPoint(Point(event->x(), height-event->y()));
	curLine->draw();
}

void LineControl::onDraw()
{
	for(Line *line:lines)
		line->draw();
}
/*
void LineControl::onMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		curLine = new Line(Point(GLUT_COORDINATE, height, x, y), Point(GLUT_COORDINATE, height, x, y));
		lines.push_back(curLine);
	}
}

void LineControl::onMotion(int x, int y)
{
	if (curLine == NULL)
		return;
	curLine->setEndPoint(Point(GLUT_COORDINATE, height, x, y));
	curLine->draw();
}*/

const vector<Line*> &LineControl::getLines()
{
	return lines;
}
