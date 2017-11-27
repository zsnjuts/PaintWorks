#ifndef LINE_H
#define LINE_H

#include "Point.h"
#include "SimpleFigure.h"

class Line: public SimpleFigure
{
public:
	Line();
	Line(const Point &begin, const Point &end);

	Point getBeginPoint() const;
	Point getEndPoint() const;
	Point getDownPoint() const;
	Point getUpPoint() const;
	void setEndPoint(const Point &p);

private:
	Point begin;
	Point end;
	Point *left;
	Point *right;
	Point *up;
	Point *down;

	void updateParameters();
	void calculatePoints();
	void bresenham01(int dx, int dy);
	void bresenham_10(int dx, int dy);
	void bresenham1inf(int dx, int dy);
	void bresenham_inf_1(int dx, int dy);
};

#endif // !LINE_H

