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
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	qDebug() << "keyPress Main" << event->text();
	//ui->mdiArea->activeSubWindow()->keyPressEvent(event);
}

void MainWindow::on_action_New_triggered()
{
	QMdiSubWindow *w = ui->mdiArea->addSubWindow(new GLWidget(this));
	ui->mdiArea->setActiveSubWindow(w);
	w->setWindowTitle(tr("画布%1").arg(ui->mdiArea->subWindowList().size()));
	w->show();
}
