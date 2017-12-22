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

bool CircleControl::setFocus(Figure *fg)
{
	for(Circle *circle:circles)
		if(circle==fg)
		{
			curCircle = circle;
			return true;
		}
	return false;
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
					pushForward(curCircle);
					return;
				}
			if(curPoint.distanceTo(curCircle->getCenter())<=5)
			{
				setCP = CENTERPOINT;
				pushForward(curCircle);
				return;
			}
			else if(curPoint.distanceTo(curCircle->getHandlePoint())<=5)
			{
				setCP = HANDLEPOINT;
				pushForward(curCircle);
				return;
			}
			else if(curCircle->isOn(curPoint))
			{
				pushForward(curCircle);
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
	case CENTERPOINT: curCircle->translate(Point(x,glY) - center); break;
	case HANDLEPOINT: curCircle->setHandlePointByRef(Point(x,glY)); break;
	default: ;
	}
}

void CircleControl::onKeyPressEvent(QKeyEvent *event)
{
	switch(event->key())
	{
	case Qt::Key_Left: curCircle->translate(Point(-2,0)); break;
	case Qt::Key_Right: curCircle->translate(Point(2,0)); break;
	case Qt::Key_Up: curCircle->translate(Point(0,2)); break;
	case Qt::Key_Down: curCircle->translate(Point(0,-2)); break;
	case Qt::Key_Q: curCircle->rotate(-2); break;
	case Qt::Key_E: curCircle->rotate(2); break;
	case Qt::Key_Plus: curCircle->scale(1.25); break; //放大为原先的5/4
	case Qt::Key_Minus: curCircle->scale(0.8); break; //缩小为原先的4/5
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

void CircleControl::onScale(double s)
{
	if(curCircle!=NULL)
		curCircle->scale(s);
}

void CircleControl::onDelete()
{
	if(curCircle==NULL)
		return;

	for(vector<Circle*>::iterator it=circles.begin();it!=circles.end();it++)
		if(curCircle==*it)
		{
			circles.erase(it);
			break;
		}
	for(vector<Figure*>::iterator it=allFigures->begin();it!=allFigures->end();it++)
		if(curCircle==*it)
		{
			allFigures->erase(it);
			break;
		}
	delete curCircle;
	curCircle = NULL;
}

void CircleControl::onClear()
{
	for(Circle *circle:circles)
	{
		for(vector<Figure*>::iterator it=allFigures->begin();it!=allFigures->end();)
		{
			if(circle==*it)
				it = allFigures->erase(it);
			else
				it++;
		}
		delete circle;
	}
	circles.clear();
	curCircle = NULL;
}
