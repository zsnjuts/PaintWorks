#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "glwidget.h"
#include <QMainWindow>
#include <QMenu>
#include <QTextEdit>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_action_New_triggered();

	void on_actionLine_triggered();

	void on_actionCircle_triggered();

	void on_actionEllipse_triggered();

	void on_actionPolygon_triggered();

	void on_actionCut_triggered();

private:
	Mode m;
	Ui::MainWindow *ui;
	QVector<GLWidget*> canvases;

	void setMode(Mode m);
};

#endif // MAINWINDOW_H
