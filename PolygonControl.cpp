#include "PolygonControl.h"

PolygonControl::PolygonControl()
{
	curLineControl = NULL;
}

PolygonControl::PolygonControl(int width, int height):FigureControl(width, height)
{
	curLineControl = NULL;
}

void PolygonControl::onMousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::LeftButton)
	{
		if (curLineControl == NULL)
			curLineControl = new LineControl(width, height);
		if (!curLineControl->getLines().empty()
			&& curLineControl->getLines().front()->getBeginPoint().distanceTo(Point(event->x(), height-event->y()))<5)
		{
			curLineControl->getLines().back()->setEndPoint(curLineControl->getLines().front()->getBeginPoint());
			polygons.push_back(new MyPolygon(curLineControl->getLines()));
			curLineControl = NULL;
		}
		else
			curLineControl->onMousePressEvent(event);
	}
}

void PolygonControl::onMousePassiveMoveEvent(QMouseEvent *event)
{
	if (curLineControl == NULL)
		return;
	curLineControl->onMouseMoveEvent(event);
}

void PolygonControl::onDraw()
{
	if(curLineControl!=NULL)
		curLineControl->onDraw();
	for(MyPolygon *polygon : polygons)
		polygon->draw();
}

void PolygonControl::onFill()
{
	polygons.back()->fillColor();
}
