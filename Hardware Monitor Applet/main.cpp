#include <QtWidgets/QApplication>
#include <external\QSingleApplication\qtsingleapplication.h>
#include "Controller.h"
#include <QTextCodec>
//#include "Tools\Data.h"

#include <GUI\mainwindow.h>

int main(int argc, char *argv[])
{
	Controller * controller = nullptr;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	QtSingleApplication a(argc, argv);


	if (a.isRunning())
	{
		if (QtSingleApplication::arguments().size() > 0 && QtSingleApplication::arguments().at(0) == "settings")
		{
			a.sendMessage(QString("OpenSettings"), 5000);
		}
		else
		{
			return 0;
		}
	}
	else
	{
		controller = new Controller(&a);
		//controller->openSettingsScreen();

		if (QtSingleApplication::arguments().size() > 1 && QtSingleApplication::arguments().at(1) == "settings")
		{
			controller->openSettingsScreen();
		}
	}

	a.exec();

	Data::removeInstance();

	if (controller != nullptr)
	{
		delete controller;
		controller = nullptr;
	}

	CoUninitialize();

	return 0;
}