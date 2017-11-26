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

protected:
	void keyPressEvent(QKeyEvent *event);

private slots:
	void on_action_New_triggered();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
