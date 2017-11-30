#include "EllipseControl.h"
#include <GL/glu.h>

EllipseControl::EllipseControl()
{
	curEllipse = NULL;
}

EllipseControl::EllipseControl(std::vector<Figure *> *figures):FigureControl(figures)
{
	curEllipse = NULL;
}

EllipseControl::EllipseControl(int width, int height):FigureControl(width, height)
{
	curEllipse = NULL;
}

void EllipseControl::onMousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::LeftButton)
	{
		if(curEllipse!=NULL)
		{
			Point curPoint(event->x(), height-event->y());
			for(Point p:curEllipse->getMarkPoints())
				if(p.distanceTo(curPoint)<=5)
				{
					setEP = MARKPOINT;
					return;
				}
		}
		curEllipse = new MyEllipse(Point(event->x(), height-event->y()), Point(event->x(), height-event->y()));
		ellipses.push_back(curEllipse);
		allFigures->push_back(curEllipse);
		setEP = ENDPOINT;
	}
}

void EllipseControl::onMouseMoveEvent(QMouseEvent *event)
{
	if (curEllipse == NULL)
		return;
	Point center = curEllipse->getCenter();
	switch(setEP)
	{
	case ENDPOINT: curEllipse->setEndPoint(Point(event->x(), height-event->y())); break;
	case MARKPOINT: curEllipse->setAxes(abs(event->x()-center.getX()), abs((height-event->y())-center.getY())); break;
	default: ;
	}
}

void EllipseControl::onDraw()
{
	for(MyEllipse *ellipse : ellipses)
		ellipse->draw();
}

void EllipseControl::onMarkDraw()
{
	if(curEllipse!=NULL)
		curEllipse->markDraw();
}
