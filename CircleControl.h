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
	CircleControl(int width, int height);
	void onMousePressEvent(QMouseEvent *event);
	void onMouseMoveEvent(QMouseEvent *event);
//	void onMouse(int button, int state, int x, int y);
//	void onMotion(int x, int y);
	void onDraw();
	void onFill();

private:
	Circle *curCircle; //当前聚焦的圆
	vector<Circle*> circles;
};

#endif // !CIRCLECONTROL_H
