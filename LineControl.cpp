#include "LineControl.h"

LineControl::LineControl()
{
	curLine = NULL;
}

LineControl::LineControl(std::vector<Figure *> *figures):FigureControl(figures)
{
	curLine = NULL;
}

LineControl::LineControl(int width, int height):FigureControl(width, height)
{
	curLine = NULL;
}

LineControl::LineControl(std::vector<Figure *> *figures, int width, int height):FigureControl(figures, width, height)
{
}

void LineControl::onMousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::LeftButton)
	{
		if(curLine!=NULL)
		{
			if(curLine->getBeginPoint().distanceTo(Point(event->x(), height-event->y()))<5)
			{
				setLP = SETBEGIN;
				return;
			}
			else if(curLine->getEndPoint().distanceTo(Point(event->x(), height-event->y()))<5)
			{
				setLP = SETEND;
				return;
			}
		}
		curLine = new Line(Point(event->x(), height-event->y()), Point(event->x(), height-event->y()));
		lines.push_back(curLine);
		allFigures->push_back(curLine);
		setLP = SETEND;
	}
}

void LineControl::onMouseMoveEvent(QMouseEvent *event)
{
	if (curLine == NULL)
		return;
	switch(setLP)
	{
	case SETBEGIN: curLine->setBeginPoint(Point(event->x(), height-event->y())); break;
	case SETEND: curLine->setEndPoint(Point(event->x(), height-event->y())); break;
	default: ;
	}
}

void LineControl::onDraw()
{
	for(Line *line:lines)
		line->draw();
}

void LineControl::onMarkDraw()
{
	if(curLine!=NULL)
		curLine->markDraw();
}

const vector<Line*> &LineControl::getLines()
{
	return lines;
}
