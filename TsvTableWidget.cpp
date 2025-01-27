#include "TsvTableWidget.h"
#include "ui_TsvTableWidget.h"

#include <QToolTip>
#include <QDebug>
#include <QClipboard>
#include "GUIHelper.h"

TsvTableWidget::TsvTableWidget(const TsvFile& table, QWidget* parent)
	: QWidget(parent)
	, ui_(new Ui::TsvTableWidget)
	, table_(table)
{
	ui_->setupUi(this);
	connect(ui_->comments_btn, SIGNAL(clicked(bool)), this, SLOT(showComments()));
	connect(ui_->copy_btn, SIGNAL(clicked(bool)), this, SLOT(copyToClipboard()));

	updateTable();
}

TsvTableWidget::~TsvTableWidget()
{
	delete ui_;
}

void TsvTableWidget::updateTable()
{
	//comments
	ui_->comments_btn->setEnabled(!table_.comments().isEmpty());

	//headers
	ui_->table->setColumnCount(table_.columnCount());
	for (int col=0; col<table_.columnCount(); ++col)
	{
		ui_->table->setHorizontalHeaderItem(col, new QTableWidgetItem(table_.headers()[col]));
	}

	//rows
	ui_->table->setRowCount(table_.count());
	for (int row=0; row<table_.count(); ++row)
	{
		for (int col=0; col<table_.columnCount(); ++col)
		{
			ui_->table->setItem(row, col, new QTableWidgetItem(table_[row][col]));
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

void TsvTableWidget::copyToClipboard()
{
	QApplication::clipboard()->setText(table_.toString());
}
