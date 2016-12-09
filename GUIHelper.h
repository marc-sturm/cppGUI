#ifndef GUIHELPER_H
#define GUIHELPER_H

#include "cppGUI_global.h"
#include <QString>
#include <QMap>
#include <QWidget>
#include <QSplitter>

///Auxilary helper functions for the GUI.
class CPPGUISHARED_EXPORT GUIHelper
{
public:
	///Shows a message dialog with title, message and additional information.
	static void showMessage(QString title, QString message, QMap<QString, QString> add_info=QMap<QString, QString>());

	///Takes ownership of a widget and shows is as a dialog.
	///Make sure a copy of the returned shared pointer exists as long as you use the dialog or the widget.
	///If @p buttons is @em true, 'ok' and 'cancel' buttons are shown.
	static QSharedPointer<QDialog> showWidgetAsDialog(QWidget* widget, QString title, bool buttons, bool modal=true);

	///Custom splitter styler
	static void styleSplitter(QSplitter* splitter);

	///Creates a horizontal line
	static QFrame* horizontalLine();

protected:
	///Constructor declared away.
	GUIHelper();
};

#endif
