#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "LineControl.h"
#include "CircleControl.h"
#include "EllipseControl.h"
#include "PolygonControl.h"
#include <QtOpenGL/QtOpenGL>
#include <GL/glu.h>
#include <QMouseEvent>
#include <vector>

enum Mode{LINE, CIRCLE, ELLIPSE, POLYGON};

class GLWidget : public QGLWidget
{
	Q_OBJECT
public:
	explicit GLWidget(QWidget *parent, Mode m);
	~GLWidget();

	void setMode(Mode m);

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);

private:
	FigureControl *curFigureControl;
	vector<FigureControl*> figureControls;
};

#endif // GLWIDGET_H
