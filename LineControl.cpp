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
	curLine = NULL;
}

bool LineControl::setFocus(Figure *fg)
{
	for(Line *line:lines)
		if(line==fg)
		{
			curLine = line;
			return true;
		}
	return false;
}

void LineControl::onMousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::LeftButton)
	{
		if(curLine!=NULL)
		{
			Point curPoint(event->x(), height-event->y());
			if(curLine->getBeginPoint().distanceTo(curPoint)<=5)
			{
				setLP = SETBEGIN;
				pushForward(curLine);
				return;
			}
			else if(curLine->getEndPoint().distanceTo(curPoint)<=5)
			{
				setLP = SETEND;
				pushForward(curLine);
				return;
			}
			else if(curLine->getCenterPoint().distanceTo(curPoint)<=5)
			{
				setLP = SETCENTER;
				pushForward(curLine);
				return;
			}
			else if(curLine->getHandlePoint().distanceTo(curPoint)<=5)
			{
				setLP = SETHANDLE;
				pushForward(curLine);
				return;
			}
			else if(curLine->isOn(curPoint))
			{
				pushForward(curLine);
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
	Point curPoint(event->x(), height-event->y());
	switch(setLP)
	{
	case SETBEGIN: curLine->setBeginPoint(curPoint); break;
	case SETEND: curLine->setEndPoint(curPoint); break;
	case SETCENTER: curLine->translate(curPoint-curLine->getCenterPoint()); break;
	case SETHANDLE: curLine->setHandlePointByRef(curPoint); break;
	default: ;
	}
}

void LineControl::onKeyPressEvent(QKeyEvent *event)
{
	switch(event->key())
	{
	case Qt::Key_Left: curLine->translate(Point(-2,0)); break;
	case Qt::Key_Right: curLine->translate(Point(2,0)); break;
	case Qt::Key_Up: curLine->translate(Point(0,2)); break;
	case Qt::Key_Down: curLine->translate(Point(0,-2)); break;
	case Qt::Key_Q: curLine->rotate(-2); break;
	case Qt::Key_E: curLine->rotate(2); break;
	case Qt::Key_Plus: curLine->scale(1.25); break; //放大为原先的5/4
	case Qt::Key_Minus: curLine->scale(0.8); break; //缩小为原先的4/5
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

void LineControl::onCut(const Point &leftDown, int width, int height)
{
	if(curLine==NULL)
		return;
	if(curLine->cut(leftDown, width, height)==false)
	{
		for(vector<Line*>::iterator it=lines.begin();it!=lines.end();it++)
			if(curLine==*it)
			{
				lines.erase(it);
				break;
			}
		for(vector<Figure*>::iterator it=allFigures->begin();it!=allFigures->end();it++)
			if(curLine==*it)
			{
				allFigures->erase(it);
				break;
			}
		delete curLine;
		curLine = NULL;
	}
}

void LineControl::onScale(double s)
{
	if(curLine==NULL)
		return;
	curLine->scale(s);
}

void LineControl::onDelete()
{
	if(curLine==NULL)
		return;

	for(vector<Line*>::iterator it=lines.begin();it!=lines.end();it++)
		if(curLine==*it)
		{
			lines.erase(it);
			break;
		}
	for(vector<Figure*>::iterator it=allFigures->begin();it!=allFigures->end();it++)
		if(curLine==*it)
		{
			allFigures->erase(it);
			break;
		}
	delete curLine;
	curLine = NULL;
}

void LineControl::onClear()
{
	for(Line *line:lines)
	{
		for(vector<Figure*>::iterator it=allFigures->begin();it!=allFigures->end();)
		{
			if(line==*it)
				it = allFigures->erase(it);
			else
				it++;
		}
		delete line;
	}
	lines.clear();
	curLine = NULL;
}

const vector<Line*> &LineControl::getLines()
{
	return lines;
}
