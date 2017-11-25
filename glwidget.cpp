#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent):QGLWidget(parent)
{
	paintGL();
}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
	//设置widget的坐标和尺寸
	setGeometry(50, 50, 50, 50);
	//设置清除时颜色
	glClearColor(0.0, 0.0, 0.0, 0);
}

void GLWidget::resizeGL(int w, int h)
{
	//视口变换
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	//投影变换
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0,(GLdouble)w/(GLdouble)h,0.1,10000.0);
	//视图变换
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,10.0,0.0,0.0,0.0,0.0,1.0,0.0);
}

void GLWidget::paintGL()
{
	qDebug() << "paintGL";
	//清屏
	glClear(GL_COLOR_BUFFER_BIT);
	//绘制矩形
	glBegin(GL_LINES);
	glColor3f(1.0,1.0,1.0);
	glVertex2f(-0.5,-0.5);
	glVertex2f(-0.5,0.5);
	glEnd();
	glFlush();
}

