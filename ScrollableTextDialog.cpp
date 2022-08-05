#include "ScrollableTextDialog.h"
#include "ui_ScrollableTextDialog.h"

ScrollableTextDialog::ScrollableTextDialog(QWidget* parent, QString title)
	: QDialog(parent)
	, ui_(new Ui::ScrollableTextDialog)
{
	ui_->setupUi(this);
	setWindowTitle(title);
}

ScrollableTextDialog::~ScrollableTextDialog()
{
	delete ui_;
}

void ScrollableTextDialog::setText(const QString& text)
{
	ui_->text_browser->setText(text);

	setCursorToStart();
}

void ScrollableTextDialog::appendLine(const QString& line)
{
	ui_->text_browser->append(line);

	setCursorToStart();
}

void ScrollableTextDialog::appendLines(QStringList& lines)
{
	foreach(const QString& line, lines)
	{
		appendLine(line);
	}

	setCursorToStart();
}

void ScrollableTextDialog::setWordWrapMode(QTextOption::WrapMode mode)
{
	ui_->text_browser->setWordWrapMode(mode);
}

void ScrollableTextDialog::setReadOnly(bool read_only)
{
	ui_->text_browser->setReadOnly(read_only);
}

void ScrollableTextDialog::setCursorToStart()
{
	QTextCursor cursor = ui_->text_browser->textCursor();
	cursor.setPosition(0);
	ui_->text_browser->setTextCursor(cursor);
}


