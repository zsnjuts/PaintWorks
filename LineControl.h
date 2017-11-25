#ifndef LINECONTROL_H
#define LINECONTROL_H

#include "Line.h"
#include "Point.h"
#include "FigureControl.h"
#include <vector>
using namespace std;

class LineControl:public FigureControl
{
public:
	LineControl();
	LineControl(int width, int height);

	void onMousePressEvent(QMouseEvent *event);
	void onMouseMoveEvent(QMouseEvent *event);
//	void onMouse(int button, int state, int x, int y);
//	void onMotion(int x, int y);
	void onDraw();

	const vector<Line*> &getLines();

private:
	Line *curLine; //当前聚焦的直线
	vector<Line*> lines;
};

#endif // !LINECONTROL_H

