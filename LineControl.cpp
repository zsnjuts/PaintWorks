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
		curLine = new Line(Point(event->x(), height-event->y()), Point(event->x(), height-event->y()));
		lines.push_back(curLine);
		allFigures->push_back(curLine);
	}
}

void LineControl::onMouseMoveEvent(QMouseEvent *event)
{
	if (curLine == NULL)
		return;
	curLine->setEndPoint(Point(event->x(), height-event->y()));
}

void LineControl::onDraw()
{
	for(Line *line:lines)
		line->draw();
}

const vector<Line*> &LineControl::getLines()
{
	return lines;
}
