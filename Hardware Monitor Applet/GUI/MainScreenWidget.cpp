#include "MainScreenWidget.h"

MainScreenWidget::MainScreenWidget(QString name, ScreenType type, bool active, QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

	ScreenName_Label->setText(name);
	ScreenType_Label->setText(Defines::translateScreenTypeEnum(type));

	if (active)
	{
		ScreenActive_Label->setText("Used");
		ScreenActive_Label->setStyleSheet("QLabel { color: rgb(0, 255, 0); }");
	}
	else
	{
		ScreenActive_Label->setText("Unused");
		ScreenActive_Label->setStyleSheet("QLabel { color: rgb(255, 0, 0); }");
	}

	QPalette p(palette());
	p.setColor(QPalette::Background, Qt::white);
	setAutoFillBackground(true);
	setPalette(p);

	connect(RemoveScreen_Button, SIGNAL(clicked()), this, SLOT(removePage()));
	connect(EditScreen_Button, SIGNAL(clicked()), this, SLOT(editpage()));

}

MainScreenWidget::~MainScreenWidget()
{
	
}

void MainScreenWidget::removePage()
{

}

void MainScreenWidget::editpage()
{

}
