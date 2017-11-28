#ifndef COMPFIGURE_H
#define COMPFIGURE_H

#include "Figure.h"
#include <vector>

class CompFigure
{
public:
	CompFigure();
	CompFigure(const std::vector<Figure*> &initFigures);
	~CompFigure();
	virtual void draw();
	virtual void clear();

protected:
	std::vector<Figure*> figures;
};

#endif // !COMPFIGURE_H
