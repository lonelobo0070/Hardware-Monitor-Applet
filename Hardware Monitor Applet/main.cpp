#include <QtWidgets/QApplication>
#include <external\QSingleApplication\qtsingleapplication.h>
#include "Controller.h"
#include "Tools\Data.h"

int main(int argc, char *argv[])
{
	Controller * controller = nullptr;

	QtSingleApplication a(argc, argv);


	if (a.isRunning())
	{
		if (QtSingleApplication::arguments().size() > 0 && QtSingleApplication::arguments().at(0) == "settings")
		{
			a.sendMessage(QString("OpenSettings"), 5000);
		}
	}
	else
	{
		controller = new Controller(&a);
		controller->openSettingsScreen();

		if (QtSingleApplication::arguments().size() > 0 && QtSingleApplication::arguments().at(0) == "settings")
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

	return 0;
}