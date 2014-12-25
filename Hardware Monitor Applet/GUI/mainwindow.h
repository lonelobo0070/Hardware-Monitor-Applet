#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "../Defines.h"
//#include "../Logitech.h"
#include "SortScreenDialog.h"
#include "MainScreenWidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	//void keyboardChanged(KeyboardTypes);

private:
	Ui::MainWindowClass ui;

private slots:
	void openScreenWizard();

}; 

#endif // MAINWINDOW_H
