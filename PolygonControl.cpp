#include "PolygonControl.h"

PolygonControl::PolygonControl()
{
	setPV = -1;
}

PolygonControl::PolygonControl(std::vector<Figure *> *figures):FigureControl(figures)
{
	setPV = -1;
}

PolygonControl::PolygonControl(int width, int height):FigureControl(width, height)
{
	setPV = -1;
}

void PolygonControl::onMousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::LeftButton)
	{
		if(!curLines.empty() && curLines.front()->getBeginPoint().distanceTo(Point(event->x(), height-event->y()))<=10)
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
			setPV = -1;
			return;
		}
		else if(curLines.empty() && !polygons.empty())
		{
			Point curPoint(event->x(), height-event->y());
			vector<Point> vtxs = polygons.back()->getVertexes();
			for(int i=0;i<vtxs.size();i++)
				if(curPoint.distanceTo(vtxs[i])<=5)
				{
					setPV = i;
					return;
				}
		}
		curLines.push_back(new Line(Point(event->x(), height-event->y()), Point(event->x(), height-event->y())));
		allFigures->push_back(curLines.back());
		setPV = -1;
	}
}

void PolygonControl::onMouseMoveEvent(QMouseEvent *event)
{
	if(!polygons.empty() && setPV>=0)
		polygons.back()->setVertex(setPV, Point(event->x(), height-event->y()));
}

void PolygonControl::onMousePassiveMoveEvent(QMouseEvent *event)
{
	if(curLines.empty())
		return;
	curLines.back()->setEndPoint(Point(event->x(), height-event->y()));
//	if(setPV<0 && !curLines.empty())
//		curLines.back()->setEndPoint(Point(event->x(), height-event->y()));
//	else if(setPV>=0)
//		polygons.back()->setVertex(setPV, Point(event->x(), height-event->y()));
}

void PolygonControl::onDraw()
{
	for(Line *line:curLines)
		line->draw();
	for(MyPolygon *polygon : polygons)
		polygon->draw();
}

void PolygonControl::onMarkDraw()
{
	if(!curLines.empty())
	{
		for(Line *line:curLines)
			line->markDraw();
	}
	else if(!polygons.empty())
	{
		polygons.back()->markDraw();
	}
}

void PolygonControl::onFill()
{
	if(!polygons.empty())
		polygons.back()->fillColor();
}
