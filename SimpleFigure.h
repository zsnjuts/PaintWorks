#ifndef SIMPLEFIGURE_H
#define SIMPLEFIGURE_H

#include "Point.h"
#include "Figure.h"

class SimpleFigure : public Figure
{
public:
	~SimpleFigure();
	virtual void draw();
	virtual void clear();
	const vector<Point*> &getPoints() const;

protected:
	vector<Point*> points;
};

#endif // SIMPLEFIGURE_H
