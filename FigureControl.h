#ifndef FIGURECONTROL_H
#define FIGURECONTROL_H

#include <QMouseEvent>

class FigureControl
{
public:
	FigureControl();
	FigureControl(int width, int height);
	void resize(int width, int height);

	virtual void onMousePressEvent(QMouseEvent *event);
	virtual void onMouseMoveEvent(QMouseEvent *event);
	virtual void onDraw();
	virtual void onFill();

protected:
	int width; //当前x轴像素点数
	int height; //当前y轴像素点数
};

#endif // !FIGURECONTROL_H

