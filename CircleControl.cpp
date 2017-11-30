#include "CircleControl.h"
#include <cmath>
#include <iostream>
using namespace std;

CircleControl::CircleControl()
{
	curCircle = NULL;
}

CircleControl::CircleControl(std::vector<Figure *> *figures):FigureControl(figures)
{
	curCircle = NULL;
}

CircleControl::CircleControl(int width, int height):FigureControl(width,height)
{
	curCircle = NULL;
}

void CircleControl::onMousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::LeftButton)
	{
		if(curCircle!=NULL)
		{
			Point curPoint(event->x(), height-event->y());
			for(Point p:curCircle->getMarkPoints())
				if(p.distanceTo(curPoint)<=5)
				{
					setCP = MARKPOINT;
					return;
				}
		}
		curCircle = new Circle(Point(event->x(), height-event->y()), 1);
		circles.push_back(curCircle);
		allFigures->push_back(curCircle);
		setCP = CIRCLEPOINT;
	}
}

void CircleControl::onMouseMoveEvent(QMouseEvent *event)
{
	if (curCircle == NULL || !(event->buttons()&Qt::LeftButton)) //检查是否为左键按下状态
		return;
	int x = event->x();
	int glY = height - event->y();
	Point center = curCircle->getCenter();
	switch(setCP)
	{
	case CIRCLEPOINT: curCircle->setRadius((int)sqrt(
											   (x-center.getX())*(x-center.getX()) + (glY-center.getY())*(glY-center.getY()) )); break;
	case MARKPOINT: curCircle->setRadius((int)max(abs(x-center.getX()), abs(glY-center.getY()))); break;
	default: ;
	}
}

void CircleControl::onDraw()
{
	for(Circle *circle:circles)
		circle->draw();
}

void CircleControl::onMarkDraw()
{
	if(curCircle!=NULL)
		curCircle->markDraw();
}

void CircleControl::onFill()
{
	if(curCircle!=NULL)
		curCircle->fillColor();
}
