#include "PolygonControl.h"

PolygonControl::PolygonControl()
{
	setPV = -1; curIdx = -1;
}

PolygonControl::PolygonControl(std::vector<Figure *> *figures):FigureControl(figures)
{
	setPV = -1; curIdx = -1;
}

PolygonControl::PolygonControl(int width, int height):FigureControl(width, height)
{
	setPV = -1; curIdx = -1;
}

void PolygonControl::onMousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::LeftButton)
	{
		//选中折线起始点，成为多边形
		if(!curLines.empty() && curLines.front()->getBeginPoint().distanceTo(Point(event->x(), height-event->y()))<=10)
		{
			curLines.back()->setEndPoint(curLines.front()->getBeginPoint());
			polygons.push_back(new MyPolygon(curLines));
			curIdx = polygons.size()-1;
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
		else if(curLines.empty() && !polygons.empty()) //选中当前多边形的标记点
		{
			Point curPoint(event->x(), height-event->y());
			vector<Point> vtxs = polygons[curIdx]->getVertexes();
			for(int i=0;i<vtxs.size();i++)
				if(curPoint.distanceTo(vtxs[i])<=5)
				{
					setPV = i;
					pushForward(polygons[curIdx]);
					return;
				}
			if(polygons[curIdx]->getCenter().distanceTo(curPoint)<=5)
			{
				setPV = -2;
				pushForward(polygons[curIdx]);
				return;
			}
			else if(polygons[curIdx]->getHandlePoint().distanceTo(curPoint)<=5)
			{
				setPV = -3;
				pushForward(polygons[curIdx]);
				return;
			}
		}
		//未选中任何点，新建折线
		curLines.push_back(new Line(Point(event->x(), height-event->y()), Point(event->x(), height-event->y())));
		allFigures->push_back(curLines.back());
		setPV = -1;
	}
}

void PolygonControl::onMouseMoveEvent(QMouseEvent *event)
{
	if(!polygons.empty())
	{
		Point curPoint(event->x(), height-event->y());
		if(setPV>=0)
			polygons[curIdx]->setVertex(setPV, curPoint);
		else if(setPV==-2)
			polygons[curIdx]->translate(curPoint - polygons[curIdx]->getCenter());
		else if(setPV==-3)
			polygons[curIdx]->setHandlePointByRef(curPoint);
	}
}

void PolygonControl::onMousePassiveMoveEvent(QMouseEvent *event)
{
	if(curLines.empty())
		return;
	curLines.back()->setEndPoint(Point(event->x(), height-event->y()));
}

void PolygonControl::onKeyPressEvent(QKeyEvent *event)
{
	if(!curLines.empty())//TODO:改一下glwidget里面的，调试一下
		return;
	switch(event->key())
	{
	case Qt::Key_Left: polygons[curIdx]->translate(Point(-2,0)); break;
	case Qt::Key_Right: polygons[curIdx]->translate(Point(2,0)); break;
	case Qt::Key_Up: polygons[curIdx]->translate(Point(0,2)); break;
	case Qt::Key_Down: polygons[curIdx]->translate(Point(0,-2)); break;
	case Qt::Key_Q: polygons[curIdx]->rotate(-2); break;
	case Qt::Key_E: polygons[curIdx]->rotate(2); break;
	case Qt::Key_Plus: polygons[curIdx]->scale(1.25); break; //放大为原先的5/4
	case Qt::Key_Minus: polygons[curIdx]->scale(0.8); break; //缩小为原先的4/5
	default: ;
	}
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
			line->plainMarkDraw();
	}
	else if(curIdx>=0)
	{
		polygons[curIdx]->markDraw();
	}
}

void PolygonControl::onFill()
{
	if(curIdx>=0)
		polygons[curIdx]->fillColor();
}

void PolygonControl::onCut(const Point &leftDown, int width, int height)
{
	if(polygons.empty() || curIdx<0)
		return;
	if(polygons[curIdx]->cut(leftDown, width, height)==false)
	{
		deletePolygon(curIdx);
		curIdx = -1;
	}
}

void PolygonControl::onDelete()
{
	if(curIdx<0)
		return;
	deletePolygon(curIdx);
	curIdx = -1;
}

void PolygonControl::onClear()
{
	for(MyPolygon *polygon:polygons)
	{
		for(vector<Figure*>::iterator it=allFigures->begin();it!=allFigures->end();)
		{
			if(polygon==*it)
				it = allFigures->erase(it);
			else
				it++;
		}
		delete polygon;
	}
	polygons.clear();
	curIdx = -1;
}

void PolygonControl::deletePolygon(int idx)
{
	if(idx<0)
		return;
	polygons.erase(polygons.begin()+idx);
	for(vector<Figure*>::iterator it=allFigures->begin();it!=allFigures->end();it++)
		if(*it==polygons[idx])
		{
			allFigures->erase(it);
			break;
		}
	delete polygons[idx];
}
