#ifndef GL3DWIDGET_H
#define GL3DWIDGET_H

#include "glwidget.h"

class GL3DWidget : public GLWidget
{
	Q_OBJECT
public:
	explicit GL3DWidget(QWidget *parent, Mode m);
	~GL3DWidget();

	virtual void setMode(Mode m);
	virtual void setEditMode(Edit e);

	virtual void onScalePlusFigures(); //放大所有图形
	virtual void onScaleMinusFigures(); //缩小所有图形
	virtual void onCutFigures(); //裁剪cw可以裁剪的所有图形
	virtual void onFillFigures(); //填充当前图形

protected:
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);

private:
	float angle; //旋转角度
};

#endif // GL3DWIDGET_H
