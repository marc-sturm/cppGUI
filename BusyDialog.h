#ifndef BUSYDIALOG_H
#define BUSYDIALOG_H

#include "cppGUI_global.h"
#include <QDialog>

namespace Ui {
class BusyDialog;
}

///Busy/Progress dialog
class CPPGUISHARED_EXPORT BusyDialog
	: public QDialog
{
	Q_OBJECT

	public:
		///Constructor
		BusyDialog(QString title, QWidget* parent = nullptr);
		///Destructor
		~BusyDialog();

	public slots:
		///Sets the message text and mode (busy or progress in percent)
		void init(QString message, bool percent);
		///Update percentage progress value.
		void update(int value);

	private:
		Ui::BusyDialog* ui_;
};

#endif // BUSYDIALOG_H
