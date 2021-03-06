#ifndef SCREENTYPEPAGE_H
#define SCREENTYPEPAGE_H

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_ScreenTypePageWidget.h"
#include "../Defines.h"

class ScreenTypePage: public QWizardPage
{
	Q_OBJECT

public:
	ScreenTypePage(KeyboardTypes keyboard, QWidget *parent = 0);
	ScreenTypePage(ScreenType type, KeyboardTypes keyboard, QWidget *parent = 0);
	virtual ~ScreenTypePage();

	ScreenType getScreenType();

protected:
	int nextId() const;

private:
	Ui::ScreenTypePageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;

};
#endif
