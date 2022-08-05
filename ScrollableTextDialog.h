#ifndef SCROLLABLETEXTDIALOG_H
#define SCROLLABLETEXTDIALOG_H

#include "cppGUI_global.h"
#include <QDialog>
#include <QTextOption>

namespace Ui {
class ScrollableTextDialog;
}

//Dialog that shows a scrollable text area
class CPPGUISHARED_EXPORT ScrollableTextDialog
	: public QDialog
{
	Q_OBJECT

public:
	//Constructor
	ScrollableTextDialog(QWidget* parent = nullptr, QString title = "");
	~ScrollableTextDialog();

	//Sets text
	void setText(const QString& text);
	//Appends a line (adds a newline before it)
	void appendLine(const QString& line);
	//Appends lines (adds a newline before earch line)
	void appendLines(QStringList& lines);

	//Set word wrap mode (default is QTextOption::WrapAtWordBoundaryOrAnywhere)
	void setWordWrapMode(QTextOption::WrapMode mode);

	//Sets read only property (default is true)
	void setReadOnly(bool read_only);

protected:
	//Sets the cursor to the start of the text
	void setCursorToStart();

private:
	Ui::ScrollableTextDialog* ui_;
};

#endif // SCROLLABLETEXTDIALOG_H
