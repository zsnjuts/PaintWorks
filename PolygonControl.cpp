#include "PolygonControl.h"

PolygonControl::PolygonControl()
{
}

PolygonControl::PolygonControl(std::vector<Figure *> *figures):FigureControl(figures)
{
}

PolygonControl::PolygonControl(int width, int height):FigureControl(width, height)
{
}

void PolygonControl::onMousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::LeftButton)
	{
		if(!curLines.empty() && curLines.front()->getBeginPoint().distanceTo(Point(event->x(), height-event->y()))<5)
		{
			curLines.back()->setEndPoint(curLines.front()->getBeginPoint());
			polygons.push_back(new MyPolygon(curLines));
			allFigures->push_back(polygons.back());
			for(Line *line:curLines)
				for(vector<Figure*>::iterator it=allFigures->begin();it!=allFigures->end();it++) //只有一个相同的，故只删除一次
					if(*it==line)
					{
						it = allFigures->erase(it);
						break;
					}
			curLines.erase(curLines.begin(), curLines.end());
		}
		else
		{
			curLines.push_back(new Line(Point(event->x(), height-event->y()), Point(event->x(), height-event->y())));
			allFigures->push_back(curLines.back());
		}
	}
}

void PolygonControl::onMousePassiveMoveEvent(QMouseEvent *event)
{
	if(curLines.empty())
		return;
	curLines.back()->setEndPoint(Point(event->x(), height-event->y()));
}

void PolygonControl::onDraw()
{
	for(Line *line:curLines)
		line->draw();
	for(MyPolygon *polygon : polygons)
		polygon->draw();
}

void PolygonControl::onFill()
{
	polygons.back()->fillColor();
}
