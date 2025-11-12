#include "TsvTableWidget.h"
#include "ui_TsvTableWidget.h"
#include <QToolTip>
#include "GUIHelper.h"
#include <QClipboard>
#include <QMenu>

TsvTableWidget::TsvTableWidget(const TsvFile& table, QWidget* parent)
	: QWidget(parent)
	, ui_(new Ui::TsvTableWidget)
	, table_(table)
{
	ui_->setupUi(this);
	connect(ui_->comments_btn, SIGNAL(clicked(bool)), this, SLOT(showComments()));
	connect(ui_->copy_btn, SIGNAL(clicked(bool)), this, SLOT(copyAllToClipboard()));
	connect(ui_->table, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customContextMenuRequested(QPoint)));
	connect(ui_->table, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(cellDoubleClicked(int, int)));

	updateTable();
}

QString TsvTableWidget::getText(int row, int col)
{
	QTableWidgetItem* item = ui_->table->item(row, col);
	if (item==nullptr) return "";

	return item->text();
}

void TsvTableWidget::updateTable()
{
	//comments
	ui_->comments_btn->setEnabled(!table_.comments().isEmpty());

	//headers
	ui_->table->setColumnCount(table_.columnCount());
	for (int col=0; col<table_.columnCount(); ++col)
	{

		ui_->table->setHorizontalHeaderItem(col, GUIHelper::createTableItem(table_.headers()[col]));
	}

	//rows
	ui_->table->setRowCount(table_.count());
	for (int row=0; row<table_.count(); ++row)
	{
		for (int col=0; col<table_.columnCount(); ++col)
		{
			ui_->table->setItem(row, col, GUIHelper::createTableItem(table_[row][col]));
		}
	}

	GUIHelper::resizeTableCellWidths(ui_->table);
	GUIHelper::resizeTableCellHeightsToFirst(ui_->table);
}

void TsvTableWidget::showComments()
{
	QPoint pos = mapToGlobal(ui_->comments_btn->pos());
	QToolTip::showText(pos, table_.comments().join("\n"));
}

void TsvTableWidget::copyAllToClipboard()
{
	QApplication::clipboard()->setText(table_.toString());
}

void TsvTableWidget::customContextMenuRequested(QPoint pos)
{
	//set up menu
	QMenu menu;
	QAction* a_copy_sel = menu.addAction(QIcon(":/Icons/Clipboard.png"), "Copy selected row(s) to clipboard");
	QAction* a_copy_cell = menu.addAction(QIcon(":/Icons/Clipboard.png"), "Copy cell under cursor to clipboard");

	//show menu
	QAction* action = menu.exec(ui_->table->viewport()->mapToGlobal(pos));
	if (action==nullptr) return;

	//execute
	if (action==a_copy_sel)
	{
		GUIHelper::copyToClipboard(ui_->table, true);
	}
	if (action==a_copy_cell)
	{
		QTableWidgetItem* item = ui_->table->itemAt(pos);
		if (item!=nullptr)
		{
			QApplication::clipboard()->setText(item->text());
		}
	}
}

void TsvTableWidget::cellDoubleClicked(int row, int /*col*/)
{
	emit rowDoubleClicked(row);
}
