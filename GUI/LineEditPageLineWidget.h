#ifndef LINEEDITPAGELINEWIDGET_H
#define LINEEDITPAGELINEWIDGET_H

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_LineEditPageLineWidget.h"
#include <QShortcut>
#include "../Defines.h"


class LineEditPageLineWidget: public QWidget
{
	Q_OBJECT

public:
	LineEditPageLineWidget(QString text = "", QWidget *parent = 0);
	virtual ~LineEditPageLineWidget();

	QString getText();

private:

	Ui::LineEditPageLineWidget ui;
};
#endif
