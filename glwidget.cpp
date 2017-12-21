#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent, Mode m):QGLWidget(parent)
{
	figureControls.push_back(new LineControl(&allFigures));
	figureControls.push_back(new CircleControl(&allFigures));
	figureControls.push_back(new EllipseControl(&allFigures));
	figureControls.push_back(new PolygonControl(&allFigures));
	cw = new CutWindow;

	setMode(m);
	setEditMode(DRAW);

	setFocusPolicy(Qt::StrongFocus);
	setMouseTracking(true); //跟踪鼠标，接收非点击鼠标移动事件
}

GLWidget::~GLWidget()
{
}

void GLWidget::setMode(Mode m)
{
	curCtrl = m;
	updateGL();
}

void GLWidget::setEditMode(Edit e)
{
	curEdit = e;
}

void GLWidget::onScalePlusFigures()
{
	for(Figure *fg:allFigures)
		fg->scale(1.25);
	updateGL();
}

void GLWidget::onScaleMinusFigures()
{
	for(Figure *fg:allFigures)
		fg->scale(0.8);
	updateGL();
}

void GLWidget::onCutFigures()
{
	if(cw->isEmpty())
		return;
	for(FigureControl *fgCtrl:figureControls)
		fgCtrl->onCut(cw->getleftDown(), cw->getWidth(), cw->getHeight());
	updateGL();
}

void GLWidget::onFillFigures()
{
	figureControls[curCtrl]->onFill();
	updateGL();
}

void GLWidget::onSave(string fileName)
{
	FILE *file;
	unsigned long imageSize;
	GLbyte *data=NULL;
	GLint viewPort[4];
	GLenum lastBuffer;
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	bmfh.bfType='MB';
	bmfh.bfReserved1=0;
	bmfh.bfReserved2=0;
	bmfh.bfOffBits=54;
	glGetIntegerv(GL_VIEWPORT,viewPort);
	imageSize=((viewPort[2]+((4-(viewPort[2]%4))%4))*viewPort[3]*3)+2;
	bmfh.bfSize=imageSize+sizeof(bmfh)+sizeof(bmih);
	data=(GLbyte*)malloc(imageSize);
	glPixelStorei(GL_PACK_ALIGNMENT,4);
	glPixelStorei(GL_PACK_ROW_LENGTH,0);
	glPixelStorei(GL_PACK_SKIP_ROWS,0);
	glPixelStorei(GL_PACK_SKIP_PIXELS,0);
	glPixelStorei(GL_PACK_SWAP_BYTES,1);
	glGetIntegerv(GL_READ_BUFFER,(GLint*)&lastBuffer);
	glReadBuffer(GL_FRONT);
	glReadPixels(0,0,viewPort[2],viewPort[3],GL_BGR,GL_UNSIGNED_BYTE,data);
	data[imageSize-1]=0;
	data[imageSize-2]=0;
	glReadBuffer(lastBuffer);
	file=fopen(fileName.c_str(),"wb");
	bmih.biSize=40;
	bmih.biWidth=viewPort[2];
	bmih.biHeight=viewPort[3];
	bmih.biPlanes=1;
	bmih.biBitCount=24;
	bmih.biCompression=0;
	bmih.biSizeImage=imageSize;
	bmih.biXPelsPerMeter=45089;
	bmih.biYPelsPerMeter=45089;
	bmih.biClrUsed=0;
	bmih.biClrImportant=0;
	fwrite(&bmfh,sizeof(bmfh),1,file);
	fwrite(&bmih,sizeof(bmih),1,file);
	fwrite(data,imageSize,1,file);
	free(data);
	fclose(file);
}

void GLWidget::onDelete()
{
	figureControls[curCtrl]->onDelete();
	updateGL();
}

void GLWidget::onClear()
{
	figureControls[LINE]->onClear();
	figureControls[CIRCLE]->onClear();
	updateGL();
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
	cw->resize(w, h);
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);//清屏
	for(Figure *figure : allFigures)
		figure->draw();
	figureControls[curCtrl]->onMarkDraw();
	if(curEdit==CUT)
		cw->draw();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	if(curEdit==CUT)
		cw->onMousePressEvent(event);
	else
		figureControls[curCtrl]->onMousePressEvent(event);
	updateGL();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	if(curEdit==CUT)
		cw->onMouseMoveEvent(event);
	else
	{
		if(event->buttons() & Qt::LeftButton) //左键按下时鼠标移动事件
			figureControls[curCtrl]->onMouseMoveEvent(event);
		else
			figureControls[curCtrl]->onMousePassiveMoveEvent(event);
	}
	updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
	switch(event->key())
	{
	case Qt::Key_0: curCtrl = LINE; break;
	case Qt::Key_1: curCtrl = CIRCLE; break;
	case Qt::Key_2: curCtrl = ELLIPSE; break;
	case Qt::Key_3: curCtrl = POLYGON; break;
	default: figureControls[curCtrl]->onKeyPressEvent(event);
	}
	updateGL();
}

