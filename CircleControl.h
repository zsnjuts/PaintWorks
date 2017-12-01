#ifndef CIRCLECONTROL_H
#define CIRCLECONTROL_H

#include "Circle.h"
#include "FigureControl.h"
#include <vector>
using namespace std;

class CircleControl:public FigureControl
{
public:
	CircleControl();
	CircleControl(std::vector<Figure*> *figures);
	CircleControl(int width, int height);

	void onMousePressEvent(QMouseEvent *event);
	void onMouseMoveEvent(QMouseEvent *event);
	void onKeyPressEvent(QKeyEvent *event);

	void onDraw();
	void onMarkDraw();
	void onFill();

private:
	enum SetCP{CIRCLEPOINT, MARKPOINT}setCP; //当前点击的点为圆上的点/标记点
	Circle *curCircle; //当前聚焦的圆
	vector<Circle*> circles;
};

#endif // !CIRCLECONTROL_H
