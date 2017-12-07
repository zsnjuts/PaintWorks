#ifndef CUTWINDOW_H
#define CUTWINDOW_H

#include "Point.h"
#include <vector>
#include <QMouseEvent>

class CutWindow
{
public:
	CutWindow();
	void resize(int boardWidth, int boardHeight);

	void onMousePressEvent(QMouseEvent *event);
	void onMouseMoveEvent(QMouseEvent *event); //鼠标按下时鼠标的移动

	Point getleftDown() const;
	int getWidth() const;
	int getHeight() const;
	bool isEmpty() const;

	void setCutWindow(const Point &begin, const Point &end);

	void draw();

private:
	int boardWidth, boardHeight; //全局窗口大小
	Point begin; //起点
	int setCWP; //当前点击的点为哪个顶点（索引）/终点
	int width, height; //剪切窗口大小
	vector<Point> vertexes; //从左下角开始，顺时针添加
};

#endif // CUTWINDOW_H
