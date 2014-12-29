#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "Ui_LineEditPageWidget.h"
#include "DataPage.h"

class LineEditPage: public QWizardPage
{
	Q_OBJECT

public:
	LineEditPage(DataPage* page, QWidget *parent = 0);
	virtual ~LineEditPage();

	bool validatePage();
	QStringList getData();

protected:
	void initializePage();

private:
	Ui::LineEditPageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;

	DataPage * dataPage_;
};