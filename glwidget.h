#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QtOpenGL>
#include <GL/glu.h>

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
};

#endif // GLWIDGET_H
