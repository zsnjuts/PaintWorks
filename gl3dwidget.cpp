#include "gl3dwidget.h"

GL3DWidget::GL3DWidget(QWidget *parent, Mode m):GLWidget(parent,m)
{
	angle = 0;
}

GL3DWidget::~GL3DWidget()
{
}

void GL3DWidget::setMode(Mode m)
{
}

void GL3DWidget::setEditMode(Edit e)
{
}

void GL3DWidget::onScalePlusFigures()
{
}

void GL3DWidget::onScaleMinusFigures()
{
}

void GL3DWidget::onCutFigures()
{
}

void GL3DWidget::onFillFigures()
{
}

void GL3DWidget::initializeGL()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
}

void GL3DWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, (GLint)w, (GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GL3DWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -4.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// 绘制立方体
	glColor3f(1.0, 1.0, 1.0);
	glEnableClientState(GL_VERTEX_ARRAY); //启用顶点数组
	GLfloat vertices[][3] = {{-1,-1,1}, {-1,1,1}, {1,1,1}, {1,-1,1}, {-1,-1,-1}, {-1,1,-1}, {1,1,-1}, {1,-1,-1}};
	glVertexPointer(3, GL_FLOAT, 0, vertices); //注册顶点数组
	GLubyte cubeIndices[] = {0,1,2,3, 2,3,7,6, 1,2,6,5, 0,1,5,4, 0,3,7,4, 4,5,6,7}; //绘制6个面的顶点绘制顺序
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
	glColor3f(0.0, 0.0, 1.0);
	GLubyte frameIndices[] = {0,1, 1,2, 2,3, 3,0, 0,4, 1,5, 2,6, 3,7, 4,5, 5,6, 6,7, 7,4}; //绘制12条棱的顶点绘制顺序
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_BYTE, frameIndices);
}

void GL3DWidget::mousePressEvent(QMouseEvent *event)
{
}

void GL3DWidget::mouseMoveEvent(QMouseEvent *event)
{
}

void GL3DWidget::keyPressEvent(QKeyEvent *event)
{
	if(event->key()==Qt::Key_Left)
		angle++;
	else if(event->key()==Qt::Key_Right)
		angle--;
	updateGL();
}

