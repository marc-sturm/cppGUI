#ifndef BUSYDIALOG_H
#define BUSYDIALOG_H

#include "cppGUI_global.h"
#include <QDialog>

namespace Ui {
class BusyDialog;
}

class CPPGUISHARED_EXPORT BusyDialog
	: public QDialog
{
	Q_OBJECT

	public:
		BusyDialog(QWidget *parent = 0);
		void setText(QString title, QString message);

	private:
		Ui::BusyDialog* ui_;
};

#endif // BUSYDIALOG_H
