#include "GUIHelper.h"
#include <QDialog>
#include <QApplication>
#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QClipboard>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QChartView>
#include <QDebug>
#include <QHeaderView>

QT_CHARTS_USE_NAMESPACE

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

QSharedPointer<QDialog> GUIHelper::createDialog(QWidget* widget, QString title, QString label, bool add_buttons)
{
	QSharedPointer<QDialog> dialog = QSharedPointer<QDialog>(new QDialog(QApplication::activeWindow()));
	dialog->setWindowFlags(Qt::Window);
	dialog->setWindowTitle(title);

	dialog->setLayout(new QBoxLayout(QBoxLayout::TopToBottom));
	dialog->layout()->setMargin(3);
	if (!label.isEmpty())
	{
		QLabel* label_widget = new QLabel(label);
		label_widget->setTextFormat(Qt::RichText);
		dialog->layout()->addWidget(label_widget);
	}
	dialog->layout()->addWidget(widget);

	//add buttons
	if (add_buttons)
	{
		QDialogButtonBox* button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
		dialog->connect(button_box, SIGNAL(accepted()), dialog.data(), SLOT(accept()));
		dialog->connect(button_box, SIGNAL(rejected()), dialog.data(), SLOT(reject()));
		dialog->layout()->addWidget(button_box);
	}

	return dialog;
}

void GUIHelper::styleSplitter(QSplitter* splitter)
{
	splitter->setHandleWidth(5);
	if (splitter->orientation()==Qt::Vertical)
	{
		splitter->setStyleSheet("QSplitter::handle:vertical { image: url(:/Icons/Splitter_vertical.png); } ");
	}
	else
	{
		splitter->setStyleSheet("QSplitter::handle:horizontal { image: url(:/Icons/Splitter_horizontal.png); } ");
	}
}

void GUIHelper::resizeTableCells(QTableWidget* widget, int max_col_width, bool first_height_for_all, int rows_used_for_column_width)
{
	//resize columns width
	widget->horizontalHeader()->setResizeContentsPrecision(rows_used_for_column_width);
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
	if (first_height_for_all)
	{
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
	else
	{
		widget->resizeRowsToContents();
	}
}

QTableWidgetItem* GUIHelper::createTableItem(const QString& text, Qt::Alignment alignment, bool editable)
{
	QTableWidgetItem* item = new QTableWidgetItem(text);

	item->setTextAlignment(alignment);
	if (!editable)
	{
		item->setFlags(item->flags()& (~Qt::ItemIsEditable));
	}

	return item;
}

QLabel* GUIHelper::createLinkLabel(const QString& text, Qt::Alignment alignment)
{
	QLabel* label = new QLabel();

	label->setMargin(2);
	label->setText(text);
	label->setAlignment(alignment);
	label->setOpenExternalLinks(true);

	return label;
}

void GUIHelper::copyToClipboard(const QTableWidget* table, bool selected_rows_only)
{
	//get selected rows
	QSet<int> selected_rows;
	if (selected_rows_only)
	{
		foreach(const QTableWidgetSelectionRange& range, table->selectedRanges())
		{
			for (int row=range.topRow(); row<=range.bottomRow(); ++row)
			{
				selected_rows << row;
			}
		}
	}

	//header
	QString output = "#";
	for (int col=0; col<table->columnCount(); ++col)
	{
		if (col!=0) output += '\t';
		output += table->horizontalHeaderItem(col)->text().replace('\t', ' ').replace('\n', ' ').replace('\r', ' ').trimmed();
	}
	output += '\n';

	//rows
	for (int row=0; row<table->rowCount(); ++row)
	{
		if (table->isRowHidden(row)) continue;

		if (selected_rows_only && !selected_rows.contains(row)) continue;

		for (int col=0; col<table->columnCount(); ++col)
		{
			if (col!=0) output += '\t';

			QString text = "";
			if (table->item(row, col)!=nullptr)
			{
				text = table->item(row, col)->text();
			}
			else if (table->cellWidget(row, col)->inherits("QLabel"))
			{
				text = qobject_cast<QLabel*>(table->cellWidget(row, col))->text();
			}
			else if (table->cellWidget(row, col)!=nullptr)
			{
				qDebug() << "Unhandled table item type " + QString(table->cellWidget(row, col)->metaObject()->className()) + " in copyToClipboard!";
			}
			output += text.replace('\t', ' ').replace('\n', ' ').replace('\r', ' ').trimmed();
		}
		output += '\n';
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

QChartView* GUIHelper::histogramChart(const Histogram& hist, QString title)
{
	QBarSet* set = new QBarSet(title);
	for(int bin=0; bin<hist.binCount(); ++bin)
	{
		set->append(hist.binValue(bin, true));
	}

	QBarSeries* series = new QBarSeries();
	series->append(set);
	QChart* chart = new QChart();
	chart->addSeries(series);
	chart->legend()->setVisible(false);
	chart->createDefaultAxes();
	chart->axisY()->setTitleText("%");
	QBarCategoryAxis* x_axis = new QBarCategoryAxis();
	for(int bin=0; bin<hist.binCount(); ++bin)
	{
		double start = hist.startOfBin(bin);
		x_axis->append(QString::number(start, 'f', 2) + "-" + QString::number(start+hist.binSize(), 'f', 2));
	}
	x_axis->setTitleText(title);
	x_axis->setLabelsAngle(90);
	chart->setAxisX(x_axis);

	QChartView* view = new QChartView(chart);
	view->setRenderHint(QPainter::Antialiasing);
	view->setMinimumSize(1000, 800);

	return view;
}

QCompleter*GUIHelper::completer(QObject* parent, const QStringList& items)
{
	QCompleter* completer = new QCompleter(items, parent);

	completer->setCompletionMode(QCompleter::PopupCompletion);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	completer->setFilterMode(Qt::MatchContains);
	completer->setCompletionRole(Qt::DisplayRole);

	return completer;
}
