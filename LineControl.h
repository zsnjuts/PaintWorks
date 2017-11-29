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
	LineControl(std::vector<Figure*> *figures);
	LineControl(int width, int height);
	LineControl(std::vector<Figure*> *figures, int width, int height);

	void onMousePressEvent(QMouseEvent *event);
	void onMouseMoveEvent(QMouseEvent *event);

	void onDraw();
	void onMarkDraw(); //绘制当前聚焦的直线的额外标记

	const vector<Line*> &getLines();

private:
	enum SetLP{SETBEGIN, SETEND} setLP; //目前更改的是起点/终点
	Line *curLine; //当前聚焦的直线
	vector<Line*> lines;
};

#endif // !LINECONTROL_H

