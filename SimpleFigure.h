#ifndef SIMPLEFIGURE_H
#define SIMPLEFIGURE_H

#include "Point.h"
#include "Figure.h"
#include <vector>

class SimpleFigure : public Figure
{
public:
	~SimpleFigure();
	virtual void draw();
	virtual void clear();
	const std::vector<Point*> &getPoints() const;

protected:
	std::vector<Point*> points;
};

#endif // SIMPLEFIGURE_H
