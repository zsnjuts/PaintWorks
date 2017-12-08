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
	void onMouseMoveEvent(QMouseEvent *event);
	void onMousePassiveMoveEvent(QMouseEvent *event);
	void onKeyPressEvent(QKeyEvent *event);

	void onDraw();
	void onMarkDraw();
	void onFill();

private:
	int setPV; //当前正在更改的顶点索引，默认为-1表示正在绘制直线，-2表示正在选中中心点进行平移
	vector<Line*> curLines; //当前聚焦的折线
	vector<MyPolygon*> polygons;
};

#endif // !POLYGONCONTROL_H

