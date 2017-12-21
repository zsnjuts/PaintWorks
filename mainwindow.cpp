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
	QMdiSubWindow *w = ui->mdiArea->addSubWindow(new GLWidget(this, m));
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

void MainWindow::on_actionCut_triggered()
{
	if(ui->mdiArea->subWindowList().empty())
		return;
	if(ui->actionCut->isChecked()) //已按下，则将所有画布设置为CUT状态
	{
		for(QMdiSubWindow *w:ui->mdiArea->subWindowList())
			dynamic_cast<GLWidget*>(w->widget())->setEditMode(CUT);
	}
	else //已按下，剪切当前画布并恢复DRAW状态，恢复未按下状态
	{
		dynamic_cast<GLWidget*>(ui->mdiArea->activeSubWindow()->widget())->onCutFigures();
		for(QMdiSubWindow *w:ui->mdiArea->subWindowList())
			dynamic_cast<GLWidget*>(w->widget())->setEditMode(DRAW);
		ui->actionCut->setChecked(false);
	}
}

void MainWindow::on_actionFill_triggered()
{
	if(ui->mdiArea->subWindowList().empty())
		return;
	dynamic_cast<GLWidget*>(ui->mdiArea->activeSubWindow()->widget())->onFillFigures();
}

void MainWindow::on_actionScalePlus_triggered()
{
	if(ui->mdiArea->subWindowList().empty())
		return;
	dynamic_cast<GLWidget*>(ui->mdiArea->activeSubWindow()->widget())->onScalePlusFigures();
}

void MainWindow::on_actionScaleMinus_triggered()
{
	if(ui->mdiArea->subWindowList().empty())
		return;
	dynamic_cast<GLWidget*>(ui->mdiArea->activeSubWindow()->widget())->onScaleMinusFigures();
}

void MainWindow::setMode(Mode m)
{
	this->m = m;
	for(QMdiSubWindow *w:ui->mdiArea->subWindowList())
		dynamic_cast<GLWidget*>(w->widget())->setMode(m);
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

void MainWindow::on_actionSave_triggered()
{
	if(ui->mdiArea->subWindowList().empty())
		return;
	QMdiSubWindow *w = ui->mdiArea->activeSubWindow();
	QString path = QFileDialog::getSaveFileName(this, tr("保存文件"), ".", tr("BMP Files(*.bmp)"));
	ui->mdiArea->setActiveSubWindow(w); //调用FileDialog之后会导致activeSubWindow为空，需要重新设置
	if(!path.isNull())
		dynamic_cast<GLWidget*>(ui->mdiArea->activeSubWindow()->widget())->onSave(path.toStdString());

}

void MainWindow::on_action_3D_triggered()
{
	QMdiSubWindow *w = ui->mdiArea->addSubWindow(new GL3DWidget(this, m));
	ui->mdiArea->setActiveSubWindow(w);
	w->setWindowTitle(tr("画布%1").arg(ui->mdiArea->subWindowList().size()));
	w->show();
}
