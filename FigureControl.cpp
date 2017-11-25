#include "FigureControl.h"

FigureControl::FigureControl()
{
}

FigureControl::FigureControl(int width, int height)
{
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

void FigureControl::onDraw()
{
}

void FigureControl::onFill()
{
}
