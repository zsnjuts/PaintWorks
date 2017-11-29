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
		curEllipse = new MyEllipse(Point(event->x(), height-event->y()), Point(event->x(), height-event->y()));
		ellipses.push_back(curEllipse);
		allFigures->push_back(curEllipse);
	}
}

void EllipseControl::onMouseMoveEvent(QMouseEvent *event)
{
	if (curEllipse == NULL)
		return;
	curEllipse->setEndPoint(Point(event->x(), height-event->y()));
}

void EllipseControl::onDraw()
{
	for(MyEllipse *ellipse : ellipses)
		ellipse->draw();
}
