#pragma once
#include "Defines.h"
#include "qdialog.h"
#include "Screen.h"
#include <QMessageBox>
#include "ui_DataDialog.h"
#include "../Tools/Data.h"

class DataDialog: public QDialog
{
	Q_OBJECT

public:
	DataDialog(Screen *, QWidget *parent);
	virtual ~DataDialog();
	QVector < Query> getData();

private slots:
	void accept();
	void reject();
	void closeEvent(QCloseEvent * event);
	void radioButtonChanged(int);
	void addSensor();
	void removeSensor();
	void clearSelectionTable();

private:

	MonitorSystem getSelectedSystem();
	void fillinData();
	void addHeaders();
	QString getSelectedSystemString();
	Screen * screenData_;

	QVector<Query> data_;

	Ui::DataDialog ui;
};