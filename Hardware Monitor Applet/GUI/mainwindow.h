#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "../Defines.h"
#include "../Logitech.h"
#include "ScreenSelectionDialog.h"
#include "NormalScreenWidget.h"
#include "GraphScreenWidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(KeyboardTypes, Logitech * lcd, QWidget *parent = 0);
	~MainWindow();

	void keyboardChanged(KeyboardTypes);

private:
	void createScreen(QString name, ScreenType type);
	void fillinAllScreens();
	void removeRemovedScreenOrder();

	Ui::MainWindowClass ui;

	QActionGroup * temperatureActionGroup_;
	QActionGroup * monitorToolActionGroup_;

	QWidget * mainWidget_;

	Logitech * lcd_;

private slots:
	void openSelectionDialog();
	void removeCurrentScreen();
	void comboBoxChanged();
	void addScreenOrder();
	void removeScreenOrder();
	void upScreenOrder();
	void downScreenOrder();
}; 

#endif // MAINWINDOW_H
