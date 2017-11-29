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

	void onDraw();
	void onMarkDraw();
	void onFill();

private:
	Circle *curCircle; //当前聚焦的圆
	vector<Circle*> circles;
};

#endif // !CIRCLECONTROL_H
