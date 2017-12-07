#include "CutWindow.h"
#include <cmath>
#include <GL/glu.h>

CutWindow::CutWindow()
{
	setCWP = -1;
}

void CutWindow::resize(int boardWidth, int boardHeight)
{
	this->boardWidth = boardWidth;
	this->boardHeight = boardHeight;
}

void CutWindow::onMousePressEvent(QMouseEvent *event)
{
	Point curPoint(event->x(), boardHeight-event->y());
	if(vertexes.empty()) //没有剪切窗口，需要初始化beginIdx
	{
		setCutWindow(curPoint, curPoint); //新建一个窗口
		setCWP = -1;
	}
	else //已经建立剪切窗口
	{
		for(int i=0;i<vertexes.size();i++) //选中的是顶点，则setCWP标记此顶点索引
			if(curPoint.distanceTo(vertexes[i])<5)
			{
				begin = vertexes[(i+2)%4];
				setCWP = i;
				return;
			}
		setCutWindow(curPoint, curPoint); //新建一个窗口
		setCWP = -1;
	}
}

void CutWindow::onMouseMoveEvent(QMouseEvent *event)
{
	if(!(event->buttons() & Qt::LeftButton)) //左键没有按下
		return;
	if(setCWP==-1)
		setCutWindow(begin, Point(event->x(), boardHeight-event->y()));
	else
		setCutWindow(begin, Point(event->x(), boardHeight-event->y())); //以对角点为起点
}

Point CutWindow::getleftDown() const
{
	return vertexes[0];
}

int CutWindow::getWidth() const
{
	return width;
}

int CutWindow::getHeight() const
{
	return height;
}

bool CutWindow::isEmpty() const
{
	return vertexes.empty();
}

void CutWindow::setCutWindow(const Point &begin, const Point &end)
{
	vertexes.clear();
	width = abs(end.getX()-begin.getX());
	height = abs(end.getY()-begin.getY());
	int minX = min(begin.getX(), end.getX());
	int minY = min(begin.getY(), end.getY());
	vertexes.push_back(Point(minX, minY));
	vertexes.push_back(Point(minX, minY+height));
	vertexes.push_back(Point(minX+width, minY+height));
	vertexes.push_back(Point(minX+width, minY));
	this->begin = begin;
}

void CutWindow::draw()
{
	if(vertexes.empty())
		return;

	//绘制虚线框
	glEnable(GL_LINE_STIPPLE); //开启虚线绘制功能
	glLineStipple(1, 0x0f0f); //虚线
	glColor3f(1.0, 0.0, 0.0); //红色
	glBegin(GL_LINE_LOOP);
	for(const Point &p:vertexes)
		glVertex2i(p.getX(), p.getY());
	glEnd();
	glFlush();
	glDisable(GL_LINE_STIPPLE); //关闭虚线绘制功能

	//绘制四个点
	for(const Point &p:vertexes)
	{
		glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		int n = 100; //绘制100个点
		GLfloat R = 5.0f; //圆的半径
		GLfloat pi = 3.1415926536f;
		for(int i=0;i<n;i++)
			glVertex2f(p.getX()+R*cos(2*pi/n*i), p.getY()+R*sin(2*pi/n*i));
		glEnd();
		glFlush();
	}
}
