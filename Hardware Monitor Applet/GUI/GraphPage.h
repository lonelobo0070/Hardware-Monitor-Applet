#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_GraphPageWidget.h"
#include "GraphPageLineWidget.h"
#include "QBoxLayout.h"
#include "../Defines.h"
#include "DataPage.h"

class GraphPage: public QWizardPage
{
	Q_OBJECT

public:
	GraphPage(DataPage* page, QWidget *parent = 0);
	GraphPage(DataPage* page, QList<LineText> lines, QList<QColor> colors, QWidget *parent = 0);
	virtual ~GraphPage();

	QMap<QString, Query> getValues();
	QList<QColor> getColors();

protected:
	int nextId() const;
	void initializePage();

private:
	void loadData(QList<LineText>, QList<QColor>);
	void fillinData();
	void removeData();

	Ui::GraphPageWidget ui;
	QWidget * widget_;
	DataPage* dataPage_;
	QVector<GraphPageLineWidget *> widgetItems_;

	QVBoxLayout * layout_;
};