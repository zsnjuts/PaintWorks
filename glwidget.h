#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "LineControl.h"
#include "CircleControl.h"
#include "EllipseControl.h"
#include "PolygonControl.h"
#include "CutWindow.h"
#include <QtOpenGL/QtOpenGL>
#include <GL/glu.h>
#include <QMouseEvent>
#include <vector>

enum Mode{LINE=0, CIRCLE, ELLIPSE, POLYGON};
enum Edit{DRAW=0, FILL, CUT};

class GLWidget : public QGLWidget
{
	Q_OBJECT
public:
	explicit GLWidget(QWidget *parent, Mode m);
	~GLWidget();

	void setMode(Mode m);
	void setEditMode(Edit e);
	void onCutFigure();

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);

private:
	int curCtrl; //当前FigureControl的索引
	int curEdit; //当前编辑状态
	CutWindow *cw; //裁剪窗口
	vector<FigureControl*> figureControls;
	vector<Figure*> allFigures; //本画布中的所有图形
};

#endif // GLWIDGET_H
