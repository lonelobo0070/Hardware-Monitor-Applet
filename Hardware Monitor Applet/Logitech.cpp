//-----------------------------------------------------------------
// Logitech File
// C++ Source - Logitech.cpp - version 0.1 (2014/09/12)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Logitech.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Logitech methods
//-----------------------------------------------------------------
Logitech::Logitech() : keyboardType_(KeyboardTypes::None), time_(0), timer_(nullptr), currentPage_(0)
{

}

Logitech::~Logitech()
{
	if (timer_ != nullptr)
	{
		timer_->stop();
		delete timer_;
		timer_ = nullptr;
	}

	for (int i = 0; i < screenList_.length(); i++)
	{
		lcd_.RemovePage(i);
		delete screenList_[i];
	}	
}

bool Logitech::initKeyboard()
{
	HRESULT hRes = lcd_.Initialize(_T("Hardware Monitor Applet"), LG_DUAL_MODE, TRUE, TRUE);

	if (hRes == S_OK)
	{

		if (lcd_.IsDeviceAvailable(LG_COLOR))
		{
			keyboardType_ = KeyboardTypes::Color;
			//startscreen_ = new StartScreen(&lcd_, "StartScreen");
			//screenList_.push_back(startscreen_);
		}

		else if (lcd_.IsDeviceAvailable(LG_MONOCHROME))
		{
			keyboardType_ = KeyboardTypes::Monochrome;

			//startscreen_ = new StartScreen(&lcd_, "StartScreen");

			//screenList_.push_back(startscreen_);
		}

		timer_ = new QTimer(this);
		connect(timer_, SIGNAL(timeout()), this, SLOT(onTimer()));
		timer_->start(30);

		return true;
	}

	return false;
}

void Logitech::onTimer()
{
	time_ += 30;

	checkButtonPresses();

	if (time_ >= 1000)
	{
		updatePage();
		time_ = 0;
	}

	lcd_.Update();
}


VOID Logitech::initLCDObjectsMonochrome()
{
	
	
}

VOID Logitech::initLCDObjectsColor()
{
	

 
}

VOID Logitech::checkButtonPresses()
{
	if (lcd_.IsDeviceAvailable(LG_COLOR))
	{
		checkbuttonPressesColor();
	}

	else if (lcd_.IsDeviceAvailable(LG_MONOCHROME))
	{
		checkbuttonPressesMonochrome();
	}
}

VOID Logitech::checkbuttonPressesMonochrome()
{
	lcd_.ModifyDisplay(LG_MONOCHROME);

	if (lcd_.ButtonTriggered(LG_BUTTON_4))
	{

	}

	else if (lcd_.ButtonTriggered(LG_BUTTON_1))
	{

	}
}

VOID Logitech::checkbuttonPressesColor()
{
	lcd_.ModifyDisplay(LG_COLOR);

	if (lcd_.ButtonTriggered(LG_BUTTON_RIGHT))
	{

	}

	else if (lcd_.ButtonTriggered(LG_BUTTON_LEFT))
	{

	}
}

void Logitech::updatePage()
{
	/*if (!screenList_.isEmpty())
	{
		screenList_[currentPage_]->update();
	}
	else
	{

	}*/
}

KeyboardTypes Logitech::getKeyboardType()
{
	return keyboardType_;
}

QVector<Screen *> Logitech::getScreenList()
{
	return screenList_;
}

void Logitech::createNormalScreen(QString name, QString background, ScreenType type, QMap<QString, Query> dataList, QStringList lines)
{
	NormalScreen * screen = new NormalScreen(&lcd_, name);
	screen->setBackground(background);
	screen->setData(optimizeData(lines, dataList));

	screenList_.append(screen);
}

QList<LineText> Logitech::optimizeData(QStringList lines, QMap<QString, Query> dataList)
{
	QList<LineText> data;

	for (QString line : lines)
	{
		QMap<QString, Query> optimizedData;

		QMap<QString, Query>::const_iterator i = dataList.constBegin();

		while (i != dataList.constEnd())
		{
			if (line.contains(i.key()))
			{
				optimizedData.insert(i.key(), i.value());
			}
			++i;
		}
		LineText text;
		text.text = line;
		text.queryMap = optimizedData;

		data.append(text);
	}

	return data;
}

/*void Logitech::createPage(QString name, ScreenType type)
{
	if (startscreen_ != nullptr)
	{
		screenList_.remove(screenList_.indexOf(startscreen_));

		delete startscreen_;
		startscreen_ = nullptr;
	}

	if (type == ScreenType::Normal)
	{
		Screen * newScreen = new NormalScreen(&lcd_, name);

		screenList_.push_back(newScreen);
	}
	else if (type == ScreenType::Graph)
	{
		Screen * newScreen = new GraphScreen(&lcd_, name);

		screenList_.push_back(newScreen);
	}

	currentPage_ = screenList_.size() - 1;
}

Screen * Logitech::getScreenData(QString name)
{
	for (Screen * screen : screenList_)
	{
		if (screen->getName() == name)
		{
			return screen;
		}
	}

	return nullptr;
}

void Logitech::addLine(QString pageName, QString text, QMap<QString, Query> dataMap)
{
	Screen * editScreen = getScreenData(pageName);

	editScreen->addLine(text, dataMap);
}

void Logitech::addFont(QString pageName, AppletFont font)
{
	Screen * editScreen = getScreenData(pageName);

	editScreen->addFont(font);
}

void Logitech::addBackground(QString pageName, QString background)
{
	QFileInfo info(background);

	QString path = Defines::getSettingsFolder() + "/Background";

	QDir makeDir(path);
	makeDir.mkpath(path);

	QString oldBackground = Defines::getSettingsFolder() + "/Background/" + pageName + "." + info.completeSuffix();

	QFile backgroundFile(oldBackground);

	backgroundFile.remove();

	QFile::copy(background, oldBackground);

	Screen * editScreen = getScreenData(pageName);

	editScreen->addbackground(oldBackground);
}

void Logitech::clearPage(QString name)
{
	Screen * editScreen = getScreenData(name);

	editScreen->clearLines();
}

void Logitech::removePage(QString name)
{
	Screen * editScreen = getScreenData(name);

	int test = screenList_.indexOf(editScreen);
	screenList_.remove(screenList_.indexOf(editScreen));

	delete editScreen;
}*/