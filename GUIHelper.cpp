#include "GUIHelper.h"
#include <QDialog>
#include <QApplication>
#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>


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

bool GUIHelper::showWidgetAsDialog(QWidget* widget, QString title, bool buttons)
{
	QDialog* dialog = new QDialog(QApplication::activeWindow());
	dialog->setWindowFlags(Qt::Window);
	dialog->setWindowTitle(title);

	dialog->setLayout(new QBoxLayout(QBoxLayout::TopToBottom));
	dialog->layout()->setMargin(3);
	dialog->layout()->addWidget(widget);


	//add buttons
	if (buttons)
	{
		QDialogButtonBox* button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
		dialog->connect(button_box, SIGNAL(accepted()), dialog, SLOT(accept()));
		dialog->connect(button_box, SIGNAL(rejected()), dialog, SLOT(reject()));
		dialog->layout()->addWidget(button_box);
	}

	//show dialog
	dialog->exec();

	//cache result
	bool accepted = dialog->result();

	//delete dialog
	dialog->layout()->removeWidget(widget);
	widget->setParent(0);
	delete dialog;

	return accepted;
}

void GUIHelper::styleSplitter(QSplitter* splitter)
{
	splitter->setHandleWidth(1);
	splitter->setStyleSheet("QSplitter::handle { background-color: #666666; margin: 1px; }");
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
