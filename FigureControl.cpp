#include "FigureControl.h"

FigureControl::FigureControl()
{
}

FigureControl::FigureControl(std::vector<Figure *> *figures)
{
	allFigures = figures;
}

FigureControl::FigureControl(int width, int height)
{
	this->width = width;
	this->height = height;
}

FigureControl::FigureControl(std::vector<Figure *> *figures, int width, int height)
{
	allFigures = figures;
	this->width = width;
	this->height = height;
}

void FigureControl::resize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void FigureControl::onMousePressEvent(QMouseEvent *event)
{
}

void FigureControl::onMouseMoveEvent(QMouseEvent *event)
{
}

void FigureControl::onMousePassiveMoveEvent(QMouseEvent *event)
{
}

void FigureControl::onKeyPressEvent(QKeyEvent *event)
{
}

void FigureControl::onDraw()
{
}

void FigureControl::onMarkDraw()
{
}

void FigureControl::onFill()
{
}

void FigureControl::onCut(const Point &leftDown, int width, int height)
{
}

void FigureControl::pushForward(Figure *figure)
{
	for(vector<Figure*>::iterator it=allFigures->begin();it!=allFigures->end();it++)
		if(*it==figure)
		{
			allFigures->erase(it);
			break;
		}
	allFigures->push_back(figure);
}
