#include "GUIHelper.h"
#include <QDialog>
#include <QApplication>
#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QClipboard>

void GUIHelper::showMessage(QString title, QString message, QMap<QString, QString> add_info)
{
	//create dialog
	QDialog* dialog = new QDialog(QApplication::activeWindow());
	dialog->window()->setWindowTitle(title);
	QGridLayout* layout = new QGridLayout();
	dialog->window()->setLayout(layout);

	//add content
	int row = 0;
	layout->addWidget(new QLabel("message:"),row ,0, Qt::AlignLeft|Qt::AlignTop);
	layout->addWidget(new QLabel(message),row ,1);
	foreach(QString key, add_info.keys())
	{
		++row;
		layout->addWidget(new QLabel(key + ":"),row ,0, Qt::AlignLeft|Qt::AlignTop);
		layout->addWidget(new QLabel(add_info[key]),row ,1);
	}

	//show
	dialog->exec();
}

QSharedPointer<QDialog> GUIHelper::showWidgetAsDialog(QWidget* widget, QString title, bool buttons, bool modal)
{
	QSharedPointer<QDialog> dialog = QSharedPointer<QDialog>(new QDialog(QApplication::activeWindow()));
	dialog->setWindowFlags(Qt::Window);
	dialog->setWindowTitle(title);

	dialog->setLayout(new QBoxLayout(QBoxLayout::TopToBottom));
	dialog->layout()->setMargin(3);
	dialog->layout()->addWidget(widget);

	//add buttons
	if (buttons)
	{
		QDialogButtonBox* button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
		dialog->connect(button_box, SIGNAL(accepted()), dialog.data(), SLOT(accept()));
		dialog->connect(button_box, SIGNAL(rejected()), dialog.data(), SLOT(reject()));
		dialog->layout()->addWidget(button_box);
	}

	//show dialog
	if (modal)
	{
		dialog->exec();
	}
	else
	{
		dialog->show();
	}

	return dialog;
}

void GUIHelper::styleSplitter(QSplitter* splitter)
{
	splitter->setHandleWidth(1);
	splitter->setStyleSheet("QSplitter::handle { background-color: #666666; margin: 1px; }");
}

void GUIHelper::resizeTableCells(QTableWidget* widget, int max_col_width)
{
	//resize columns width
	widget->resizeColumnsToContents();

	//restrict width
	if (max_col_width>0)
	{
		for (int i=0; i<widget->columnCount(); ++i)
		{
			if (widget->columnWidth(i)>max_col_width)
			{
				widget->setColumnWidth(i, max_col_width);
			}
		}
	}

	//determine row height
	int height = -1;
	for (int i=0; i<widget->rowCount(); ++i)
	{
		if (!widget->isRowHidden(i))
		{
			widget->resizeRowToContents(i);
			height = widget->rowHeight(i);
			break;
		}
	}

	//set row height
	if (height!=-1)
	{
		for (int i=0; i<widget->rowCount(); ++i)
		{
			widget->setRowHeight(i, height);
		}
	}
}

void GUIHelper::copyToClipboard(const QTableWidget* table)
{
	//header
	QString output = "#";
	for (int col=0; col<table->columnCount(); ++col)
	{
		if (col!=0) output += "\t";
		output += table->horizontalHeaderItem(col)->text();
	}
	output += "\n";

	//rows
	for (int row=0; row<table->rowCount(); ++row)
	{
		if (table->isRowHidden(row)) continue;

		for (int col=0; col<table->columnCount(); ++col)
		{
			if (col!=0) output += "\t";
			output += table->item(row, col)->text();
		}
		output += "\n";
	}

	QApplication::clipboard()->setText(output);
}

QFrame* GUIHelper::horizontalLine()
{
	QFrame* line = new QFrame();
	line->setObjectName("line");
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	line->setMinimumHeight(3);
	return line;
}
