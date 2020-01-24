#ifndef TSVTABLEWIDGET_H
#define TSVTABLEWIDGET_H

#include <QWidget>
#include "TsvFile.h"

#include "cppGUI_global.h"

namespace Ui {
class TsvTableWidget;
}

class CPPGUISHARED_EXPORT TsvTableWidget
	: public QWidget
{
	Q_OBJECT

public:
	TsvTableWidget(const TsvFile& table, QWidget *parent = 0);
	~TsvTableWidget();

protected slots:
	void updateTable();
	void showComments();
	void copyToClipboard();

private:
	Ui::TsvTableWidget* ui_;
	const TsvFile& table_;
};

#endif // TSVTABLEWIDGET_H
