#include "ScreenTypePage.h"


ScreenTypePage::ScreenTypePage(QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr)
{
	setTitle(tr("Type selection"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout;
	layout_->addWidget(widget_);
	setLayout(layout_);
}

ScreenTypePage::~ScreenTypePage()
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

ScreenType ScreenTypePage::getScreenType()
{
	if (ui.NormalScreen_radioButton->isChecked())
	{
		return ScreenType::Normal;
	}
	else if (ui.GraphScreen_radioButton->isChecked())
	{
		return ScreenType::Graph;
	}

	return ScreenType::No;
}

int ScreenTypePage::nextId() const
{
	return Page::Page_Data;
}