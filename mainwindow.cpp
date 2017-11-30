#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle(tr("PaintWorks"));

	setCentralWidget(ui->mdiArea);
	ui->mdiArea->setViewMode(QMdiArea::TabbedView); //设置视口模式：tabBar模式
	ui->mdiArea->setTabPosition(QTabWidget::North); //设置tabBar的方位
	ui->mdiArea->setTabsClosable(true); //tab上方有一个关闭小按钮
	ui->mdiArea->setTabsMovable(true); //可拖动tab在tabBar上移动
	ui->mdiArea->setTabShape(QTabWidget::Triangular); //设置tab形状：梯形

	setMode(LINE); //初始模式
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_action_New_triggered()
{
	//TODO:关闭标签页的时候应该删除对应的GLWidget
	canvases.push_back(new GLWidget(this, m));
	QMdiSubWindow *w = ui->mdiArea->addSubWindow(canvases.back());
	ui->mdiArea->setActiveSubWindow(w);
	w->setWindowTitle(tr("画布%1").arg(ui->mdiArea->subWindowList().size()));
	w->show();
}

void MainWindow::on_actionLine_triggered()
{
	setMode(LINE);
}

void MainWindow::on_actionCircle_triggered()
{
	setMode(CIRCLE);
}

void MainWindow::on_actionEllipse_triggered()
{
	setMode(ELLIPSE);
}

void MainWindow::on_actionPolygon_triggered()
{
	setMode(POLYGON);
}

void MainWindow::setMode(Mode m)
{
	this->m = m;
	for(GLWidget *wgt : canvases)
		wgt->setMode(m);
	ui->actionLine->setChecked(false);
	ui->actionCircle->setChecked(false);
	ui->actionEllipse->setChecked(false);
	ui->actionPolygon->setChecked(false);
	switch(m)
	{
	case LINE: ui->actionLine->setChecked(true); break;
	case CIRCLE: ui->actionCircle->setChecked(true); break;
	case ELLIPSE: ui->actionEllipse->setChecked(true); break;
	case POLYGON: ui->actionPolygon->setChecked(true); break;
	default: ;
	}
}
