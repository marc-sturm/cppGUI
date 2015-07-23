#include "BusyDialog.h"
#include "ui_BusyDialog.h"

BusyDialog::BusyDialog(QString title, QWidget* parent)
	: QDialog(parent, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint| Qt::WindowSystemMenuHint)
	, ui_(new Ui::BusyDialog())
{
	ui_->setupUi(this);
	setWindowTitle(title);
	show();
}

BusyDialog::~BusyDialog()
{
	hide();
}

void BusyDialog::init(QString message, bool percent)
{
	ui_->message->setText(message);

	if (percent)
	{
		ui_->bar->setMinimum(0);
		ui_->bar->setMaximum(100);
		ui_->bar->setValue(0);
	}
	else
	{
		ui_->bar->setMinimum(0);
		ui_->bar->setMaximum(0);
	}
}

void BusyDialog::update(int value)
{
	ui_->bar->setValue(value);
}


