#include "DataPage.h"


DataPage::DataPage(QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr)
{
	setTitle(tr("Select data"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout;
	layout_->addWidget(widget_);
	setLayout(layout_);

	registerField("SelectedData", ui.SelectedItems_tableWidget);

	ui.HWiNFO_tableWidget->hideColumn(0);
	ui.OHM_tableWidget->hideColumn(0);
	ui.SelectedItems_tableWidget->hideColumn(0);

	connect(ui.Add_pushButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
	connect(ui.Remove_pushButton, SIGNAL(clicked()), this, SLOT(removeButtonClicked()));

	registerField("ScreenData", ui.SelectedItems_tableWidget);

	loadData(MonitorSystem::HWiNFO);
	loadData(MonitorSystem::OHM);
}

DataPage::~DataPage()
{
	if (widget_ == nullptr)
	{
		delete widget_;
		widget_ = nullptr;
	}

	if (layout_ == nullptr)
	{
		delete layout_;
		layout_ = nullptr;
	}
}

bool DataPage::validatePage()
{
	return true;
}

void DataPage::loadData(MonitorSystem system)
{
	QVector<HardwareSensor> data = Data::Instance()->getAllData(system);

	QTableWidget * widget = nullptr;

	if (system == MonitorSystem::HWiNFO)
	{
		widget = ui.HWiNFO_tableWidget;
	}
	else if (system == MonitorSystem::OHM)
	{
		widget = ui.OHM_tableWidget;
	}

	for (int row = 0; row < data.size(); row++)
	{
		HardwareSensor sensor = data[row];

		widget->insertRow(row);

		QTableWidgetItem * idItem = new QTableWidgetItem();
		QTableWidgetItem * nameItem = new QTableWidgetItem();
		QTableWidgetItem * minItem = new QTableWidgetItem();
		QTableWidgetItem * maxItem = new QTableWidgetItem();
		QTableWidgetItem * currentItem = new QTableWidgetItem();

		idItem->setText(sensor.id);
		nameItem->setText(sensor.name);
		minItem->setText(QString::number(sensor.min));
		maxItem->setText(QString::number(sensor.max));
		currentItem->setText(QString::number(sensor.value));

		widget->setItem(row, 0, idItem);
		widget->setItem(row, 1, nameItem);
		widget->setItem(row, 2, minItem);
		widget->setItem(row, 3, maxItem);
		widget->setItem(row, 4, currentItem);
	}
}

void DataPage::addButtonClicked()
{
	QList<QTableWidgetItem*> selectedItems;
	QTableWidget * tableWidget;
	QString system;
	QString * value;

	int newRow = ui.SelectedItems_tableWidget->rowCount();

	if (ui.TabWidget->currentWidget() == ui.OHMTab)
	{
		selectedItems = ui.OHM_tableWidget->selectedItems();
		tableWidget = ui.OHM_tableWidget;

		system = Defines::translateMonitorSystemEnum(MonitorSystem::OHM);
	}
	else if (ui.TabWidget->currentWidget() == ui.HWiNFOTab)
	{
		selectedItems = ui.HWiNFO_tableWidget->selectedItems();
		tableWidget = ui.HWiNFO_tableWidget;

		system = Defines::translateMonitorSystemEnum(MonitorSystem::HWiNFO);
	}

	for (QTableWidgetItem * item : selectedItems)
	{
		Query queryItem;
		queryItem.identifier = tableWidget->item(item->row(), 0)->text();
		queryItem.name = tableWidget->item(item->row(), 1)->text();
		queryItem.system = Defines::translateMonitorSystemEnum(system);
		queryItem.value = Defines::translateQueryValueEnum(tableWidget->horizontalHeaderItem(item->column())->text());
		queryItem.precision = 0;

		if (isUnique(queryItem))
		{
			ui.SelectedItems_tableWidget->insertRow(newRow);

			QTableWidgetItem * idItem = new QTableWidgetItem();
			QTableWidgetItem * nameItem = new QTableWidgetItem();
			QTableWidgetItem * systemItem = new QTableWidgetItem();
			QTableWidgetItem * valueItem = new QTableWidgetItem();
			QTableWidgetItem * precisionItem = new QTableWidgetItem();

			idItem->setText(queryItem.identifier);
			nameItem->setText(queryItem.name);
			systemItem->setText(system);
			valueItem->setText(tableWidget->horizontalHeaderItem(item->column())->text());
			precisionItem->setText(QString::number(0));

			ui.SelectedItems_tableWidget->setItem(newRow, 0, idItem);
			ui.SelectedItems_tableWidget->setItem(newRow, 1, systemItem);
			ui.SelectedItems_tableWidget->setItem(newRow, 2, nameItem);
			ui.SelectedItems_tableWidget->setItem(newRow, 3, valueItem);
			ui.SelectedItems_tableWidget->setItem(newRow, 4, precisionItem);

			newRow += 1;
		}
	}
}

void DataPage::removeButtonClicked()
{
	QList<QTableWidgetItem*> items = ui.SelectedItems_tableWidget->selectedItems();

	ui.SelectedItems_tableWidget->removeRow(items[0]->row());
}

bool DataPage::isUnique(Query item)
{
	for (int row = 0; row < ui.SelectedItems_tableWidget->rowCount(); row++)
	{
		QTableWidget * widget = ui.SelectedItems_tableWidget;

		if (widget->item(row, 0)->text() == item.identifier &&
			widget->item(row, 1)->text() == Defines::translateMonitorSystemEnum(item.system) &&
			widget->item(row, 2)->text() == item.name &&
			widget->item(row, 3)->text() == Defines::translateQueryValueEnum(item.value))
		{
			return false;
		}
	}

	return true;
}