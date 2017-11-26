#ifndef AREA_H
#define AREA_H

#include "Point.h"
#include <vector>
using namespace std;

class Area
{
public:
	virtual void fillColor();
	virtual void clearColor();

protected:
	vector<Point*> fillPoints;
};

#endif // !AREA_H

