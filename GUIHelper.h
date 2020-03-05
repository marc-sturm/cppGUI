#ifndef GUIHELPER_H
#define GUIHELPER_H

#include "cppGUI_global.h"
#include "Histogram.h"
#include "ClickableLabel.h"
#include <QString>
#include <QMap>
#include <QWidget>
#include <QSplitter>
#include <QTableWidget>
#include <QCompleter>

namespace QtCharts
{
   class QChartView; //forward declaration so that not all tools need to import the Qt charts namespace
}

///Auxilary helper functions for the GUI.
class CPPGUISHARED_EXPORT GUIHelper
{
public:
	///Shows a message dialog with title, message and additional information.
	static void showMessage(QString title, QString message, QMap<QString, QString> add_info=QMap<QString, QString>());

	///Creates a dialog from a widget. The dialog takes ownership of the widget.
	static QSharedPointer<QDialog> createDialog(QWidget* widget, QString title, QString label="", bool add_buttons=false);

	///Custom splitter styler
	static void styleSplitter(QSplitter* splitter);

	///Resize column width and hight
	static void resizeTableCells(QTableWidget* widget, int max_col_width=-1, bool first_height_for_all=true);

	///Creates a table cell item
	static QTableWidgetItem* createTableItem(const QString& text, Qt::Alignment alignment=Qt::AlignLeft|Qt::AlignTop, bool editable=false);

	///Creates a label that can open links in the text.
	static QLabel* createLinkLabel(const QString& text, Qt::Alignment alignment=Qt::AlignLeft|Qt::AlignTop);

	///Copy all content of a table widget to the clipboard
	static void copyToClipboard(const QTableWidget* table);

	///Creates a horizontal line
	static QFrame* horizontalLine();

	///Creates a chart with a histogram
	static QtCharts::QChartView* histogramChart(const Histogram& hist, QString title);

	///Creates a list-based auto-completer
	static QCompleter* completer(QObject* parent, const QStringList& items);

protected:
	///Constructor declared away.
	GUIHelper() = delete;
};

#endif
