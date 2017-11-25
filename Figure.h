#ifndef FIGURE_H
#define FIGURE_H

#include "Point.h"
#include <vector>
#include <GL/glu.h>
using namespace std;

class Figure
{
public:
	~Figure();
	virtual void draw();
	virtual void clear();
	const vector<Point*> &getPoints() const;

protected:
	vector<Point*> points;
};

#endif // !FIGURE_H

