#include "mainwindow.h"
#include "../Controller.h"

MainWindow::MainWindow(Logitech * logitech, Controller * controller, QWidget *parent)
	: QMainWindow(parent), logitech_(logitech), controller_(controller)
{
	ui.setupUi(this);

	keyboardChanged(logitech->getKeyboardType());

	connect(ui.AddScreen_Button, SIGNAL(clicked()), this, SLOT(openScreenWizard()));
	connect(ui.Order_pushButton, SIGNAL(clicked()), this, SLOT(openOrderWindow()));
	connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(closeWindow()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(closeProgram()));
	connect(ui.actionFahrenheit, SIGNAL(triggered()), this, SLOT(settingsChanged()));
	connect(ui.actionCelsius, SIGNAL(triggered()), this, SLOT(settingsChanged()));

	fillinPages();
}

MainWindow::~MainWindow()
{
	removePages();
}

void MainWindow::keyboardChanged(KeyboardTypes type)
{
	if (type == KeyboardTypes::None)
	{
		ui.statusBar->showMessage(tr("No Logitech keyboard found!!"));
	}
	else if (type == KeyboardTypes::Monochrome)
	{
		ui.statusBar->showMessage(tr("Connected to: Logitech monochrome (G15, G15s, G510) keyboard"));
	}
	else
	{
		ui.statusBar->showMessage(tr("Connected to: Logitech color (G19, G19s) keyboard"));
	}

}

void MainWindow::closeEvent(QCloseEvent * event)
{
	closeWindow();
}

void MainWindow::closeWindow()
{
	controller_->closeSettingsScreen();
}

void MainWindow::closeProgram()
{
	controller_->quitApplication();
}

void MainWindow::reportIssue()
{
	QUrl url("https://bitbucket.org/jimmyD/hardware-monitor-applet-for-logitech-lcd/issues?status=new&status=open");
	QDesktopServices::openUrl(url);
}

void MainWindow::openScreenWizard()
{
	CreateScreenWizard * wizard = new CreateScreenWizard(logitech_);
	wizard->exec();
	
	delete wizard;

	refreshPages();
}

void MainWindow::settingsChanged()
{
	if (ui.actionCelsius->isChecked())
	{
		Settings::getInstance()->setTemperature(Temperature::Celsius);
	}
	else if (ui.actionFahrenheit->isChecked())
	{
		Settings::getInstance()->setTemperature(Temperature::Fahrenheit);
	}
}

void MainWindow::fillinPages()
{
	QVector<Screen *> pages = logitech_->getScreenList();

	for (int i = 0; i < pages.size(); i++)
	{
		MainScreenWidget * widget = new MainScreenWidget(this, logitech_, pages[i]->getName(), pages[i]->getScreenType(), logitech_->isScreenActive(pages[i]->getName()));

		ui.ScreenList_Layout->addWidget(widget);

		widgetList_.append(widget);
	}
}

void MainWindow::removePages()
{
	for (QWidget * widget : widgetList_)
	{
		ui.ScreenList_Layout->removeWidget(widget);
		delete widget;
	}

	widgetList_.clear();
}

void MainWindow::refreshPages()
{
	removePages();
	fillinPages();
}


void MainWindow::openOrderWindow()
{
	OrderWindow * window = new OrderWindow(logitech_);

	window->exec();

	refreshPages();

	delete window;
}