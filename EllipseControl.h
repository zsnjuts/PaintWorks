#ifndef ELLIPSECONTROL_H
#define ELLIPSECONTROL_H

#include "Ellipse.h"
#include "FigureControl.h"
#include <vector>
using namespace std;

class EllipseControl:public FigureControl
{
public:
	EllipseControl();
	EllipseControl(std::vector<Figure*> *figures);
	EllipseControl(int width, int height);

	void onMousePressEvent(QMouseEvent *event);
	void onMouseMoveEvent(QMouseEvent *event);
	void onKeyPressEvent(QKeyEvent *event);

	void onDraw();
	void onMarkDraw();

private:
	enum SetEP{ENDPOINT, MARKPOINT, CENTERPOINT, HANDLEPOINT}setEP; //当前点击的点为终点/标记点
	MyEllipse *curEllipse; //当前正在绘制的椭圆
	vector<MyEllipse*> ellipses; //绘制好的椭圆
};

#endif // !ELLIPSECONTROL_H

