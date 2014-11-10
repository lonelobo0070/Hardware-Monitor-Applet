#pragma once

#include <external\Logitech\EZ_LCD.h>
#include <qdir.h>
#include <qpixmap.h>
#include <QtWinExtras\qwinfunctions.h>
#include <QVector>
#include <qactiongroup.h>
#include <qobject.h>
#include <qtimer.h>
#include <qfont.h>
#include <qmap.h>

enum KeyboardTypes {Color, Monochrome, None};
enum ScreenType {Normal, Graph, Start, No};
enum QueryValue {Name, Current, Max, Min};
enum MonitorSystem { OHM, HWiNFO, NONE };

struct Query{
	MonitorSystem system;
	QString identifier;
	QString name;
	QueryValue value;
};

struct LineText{
	QString text;
	QMap<QString, Query> queryMap;
	HANDLE textHandle;
};

struct AppletFont{
	QFont name;
	int height;
	double lineSpace;
	QColor color;
};

struct HardwareSensor{
	string id;
	string name;
	double value;
	double max;
	double min;
};