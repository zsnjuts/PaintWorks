#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent):QGLWidget(parent)
{
	lineControl = new LineControl;
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
	//设置widget的坐标和尺寸
	setGeometry(50, 50, 50, 50);
	//设置清除时颜色
	glClearColor(1.0, 1.0, 1.0, 0);
}

void GLWidget::resizeGL(int w, int h)
{
	//投影变换
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (double)w, 0.0, (double)h);

	//视图变换
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0,(GLsizei)w,(GLsizei)h);

	//设置FigureControl
	lineControl->resize(w, h);
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);//清屏
	lineControl->onDraw();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	lineControl->onMousePressEvent(event);
	updateGL();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	lineControl->onMouseMoveEvent(event);
	updateGL();
}

