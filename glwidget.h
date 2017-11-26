#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "LineControl.h"
#include "CircleControl.h"
#include <QtOpenGL/QtOpenGL>
#include <GL/glu.h>
#include <QMouseEvent>

class GLWidget : public QGLWidget
{
	Q_OBJECT
public:
	explicit GLWidget(QWidget *parent=0);
	~GLWidget();

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);

private:
	LineControl *lineControl;
	CircleControl *circleControl;
};

#endif // GLWIDGET_H
