#ifndef FIGURECONTROL_H
#define FIGURECONTROL_H

#include "Figure.h"
#include <QMouseEvent>
#include <vector>

class FigureControl
{
public:
	FigureControl();
	FigureControl(std::vector<Figure*> *figures);
	FigureControl(int width, int height);
	FigureControl(std::vector<Figure*> *figures, int width, int height);
	void resize(int width, int height);

	virtual void onMousePressEvent(QMouseEvent *event);
	virtual void onMouseMoveEvent(QMouseEvent *event); //鼠标按下时鼠标的移动
	virtual void onMousePassiveMoveEvent(QMouseEvent *event); //鼠标未被按下时鼠标的移动

	virtual void onDraw(); //绘制所有图形（不带标记）
	virtual void onMarkDraw(); //为当前图形添加标记
	virtual void onFill();

protected:
	int width; //当前x轴像素点数
	int height; //当前y轴像素点数
	std::vector<Figure*> *allFigures; //指向全局的Figure数组
};

#endif // !FIGURECONTROL_H

