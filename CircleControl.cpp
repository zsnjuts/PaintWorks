#include "CircleControl.h"
#include <cmath>
#include <iostream>
using namespace std;

CircleControl::CircleControl()
{
}

CircleControl::CircleControl(int width, int height):FigureControl(width,height)
{
	curCircle = NULL;
}

void CircleControl::onMousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::LeftButton)
	{
		curCircle = new Circle(Point(event->x(), height-event->y()), 1);
		curCircle->draw();
		circles.push_back(curCircle);
	}
}

void CircleControl::onMouseMoveEvent(QMouseEvent *event)
{
	if (curCircle == NULL || !(event->buttons()&Qt::LeftButton)) //检查是否为左键按下状态
		return;
	int x = event->x();
	int glY = height - event->y();
	Point center = curCircle->getCenter();
	curCircle->setRadius((int)sqrt(
		(x - center.getX())*(x - center.getX())+ (glY - center.getY())*(glY - center.getY()) ));
	curCircle->draw();
}

void CircleControl::onDraw()
{
	for(Circle *circle:circles)
		circle->draw();
}
/*
void CircleControl::onMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		curCircle = new Circle(Point(GLUT_COORDINATE, 400, x, y), 1);
		curCircle->draw();
		circles.push_back(curCircle);
	}
}

void CircleControl::onMotion(int x, int y)
{
	if (curCircle == NULL)
		return;
	Point center = curCircle->getCenter();
	int glY = Point::getBoardHeight() - y;
	curCircle->setRadius((int)sqrt(
		(x - center.getX())*(x - center.getX())+ (glY - center.getGlY())*(glY - center.getGlY()) ));
	curCircle->draw();
}*/

void CircleControl::onFill()
{
	cout << "fill" << endl;
	curCircle->fillColor();
}
