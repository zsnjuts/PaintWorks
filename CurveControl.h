#ifndef CURVECONTROL_H
#define CURVECONTROL_H

#include "Curve.h"
#include "FigureControl.h"

class CurveControl:public FigureControl
{
public:
	CurveControl();
	CurveControl(std::vector<Figure*> *figures);
	CurveControl(int width, int height);
	~CurveControl();
	bool setFocus(Figure *fg);

	void onMousePressEvent(QMouseEvent *event);
	void onMouseMoveEvent(QMouseEvent *event);

	void onDraw();
	void onMarkDraw();

	void onScale(double s);
	void onDelete();
	void onClear();

private:
	int setCV; //当前正在更改的控制点索引；-1表示正在绘制控制点,-2表示选中了中心点,-3表示选中了handle点
	int curIdx; //当前聚焦的曲线索引
	vector<Point> curVtxs; //当前聚焦的控制点
	vector<Curve*> curves; //添加/删除都要在allFigures同步进行

	void deleteCurve(int idx); //删除特定索引的Curve
};

#endif // CURVECONTROL_H
