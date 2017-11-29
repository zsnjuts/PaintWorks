#ifndef POLYGONCONTROL_H
#define POLYGONCONTROL_H

#include "Polygon.h"
#include "LineControl.h"
#include "FigureControl.h"
#include <vector>
using namespace std;

class PolygonControl:public FigureControl
{
public:
	PolygonControl();
	PolygonControl(std::vector<Figure*> *figures);
	PolygonControl(int width, int height);

	void onMousePressEvent(QMouseEvent *event);
	void onMousePassiveMoveEvent(QMouseEvent *event);

	void onDraw();
	void onFill();

private:
	vector<Line*> curLines; //当前聚焦的折线
	vector<MyPolygon*> polygons;
};

#endif // !POLYGONCONTROL_H

