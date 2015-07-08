#include "BusyDialog.h"
#include "ui_BusyDialog.h"

BusyDialog::BusyDialog(QWidget* parent)
	: QDialog(parent, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint| Qt::WindowSystemMenuHint)
	, ui_(new Ui::BusyDialog())
{
	ui_->setupUi(this);
}

void BusyDialog::setText(QString title, QString message)
{
	setWindowTitle(title);
	ui_->message->setText(message);
}


