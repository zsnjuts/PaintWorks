#include "CompFigure.h"

CompFigure::CompFigure()
{
}

CompFigure::CompFigure(const std::vector<Figure*>& initFigures):figures(initFigures)
{
}

CompFigure::~CompFigure()
{
	clear();
}

void CompFigure::draw()
{
	for (auto it : figures)
		it->draw();
}

void CompFigure::clear()
{
	for (auto it : figures)
		it->clear();
}
