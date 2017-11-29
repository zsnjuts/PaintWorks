#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent, Mode m):QGLWidget(parent)
{
	figureControls.push_back(new LineControl(&allFigures));
	figureControls.push_back(new CircleControl(&allFigures));
	figureControls.push_back(new EllipseControl(&allFigures));
	figureControls.push_back(new PolygonControl(&allFigures));
	setMode(m);

	setFocusPolicy(Qt::StrongFocus);
	setMouseTracking(true); //跟踪鼠标，接收非点击鼠标移动事件
}

GLWidget::~GLWidget()
{
}

void GLWidget::setMode(Mode m)
{
	curCtrl = m;
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
	for(FigureControl *figureControl : figureControls)
		figureControl->resize(w, h);
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);//清屏
	for(Figure *figure : allFigures)
		figure->draw();
	figureControls[curCtrl]->onMarkDraw();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	figureControls[curCtrl]->onMousePressEvent(event);
	updateGL();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	if(event->buttons() & Qt::LeftButton) //左键按下时鼠标移动事件
		figureControls[curCtrl]->onMouseMoveEvent(event);
	else
		figureControls[curCtrl]->onMousePassiveMoveEvent(event);
	updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
	if(event->key()==Qt::Key_F)
		figureControls[curCtrl]->onFill();
	else
	{
		switch(event->key())
		{
		case Qt::Key_0: curCtrl = LINE; break;
		case Qt::Key_1: curCtrl = CIRCLE; break;
		case Qt::Key_2: curCtrl = ELLIPSE; break;
		case Qt::Key_3: curCtrl = POLYGON; break;
		default: ;
		}
	}
	updateGL();
}

