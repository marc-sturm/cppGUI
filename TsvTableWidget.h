#ifndef TSVTABLEWIDGET_H
#define TSVTABLEWIDGET_H

#include "cppGUI_global.h"
#include <QWidget>
#include "TsvFile.h"

namespace Ui {
class TsvTableWidget;
}

///Generic table widget for showing a TSV file
class CPPGUISHARED_EXPORT TsvTableWidget
	: public QWidget
{
	Q_OBJECT

public:
	TsvTableWidget(const TsvFile& table, QWidget* parent);
	QString getText(int row, int col);

signals:
	void rowDoubleClicked(int row);

protected slots:
	void updateTable();
	void showComments();
	void copyAllToClipboard();
	void customContextMenuRequested(QPoint pos);
	void cellDoubleClicked(int row, int col);

private:
	Ui::TsvTableWidget* ui_;
	const TsvFile& table_;
};

#endif // TSVTABLEWIDGET_H
