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
	void onKeyPressEvent(QKeyEvent *event);

	void onDraw();
	void onMarkDraw(); //绘制当前聚焦的直线的额外标记
	void onCut(const Point &leftDown, int width, int height); //对所有直线进行裁剪
	void onDelete();

	const vector<Line*> &getLines();

private:
	enum SetLP{SETBEGIN, SETEND, SETCENTER, SETHANDLE} setLP; //目前更改的是起点/终点
	Line *curLine; //当前聚焦的直线
	vector<Line*> lines; //注意：删除直线时需要同时删除lines和allFigures中的直线
};

#endif // !LINECONTROL_H

