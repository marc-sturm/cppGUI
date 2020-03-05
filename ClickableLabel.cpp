#include "ClickableLabel.h"
#include <QDesktopServices>

ClickableLabel::ClickableLabel(QWidget* parent)
	: QLabel(parent)
{
	connect(this, SIGNAL(linkActivated(QString)), this, SLOT(openUrl(QString)));
}

void ClickableLabel::mouseReleaseEvent(QMouseEvent* e)
{
	if (e->button()!=Qt::LeftButton)
	{
		e->ignore();
		return;
	}

	e->accept();
	emit clicked(e->globalPos());
}

void ClickableLabel::openUrl(QString url)
{
	QDesktopServices::openUrl(QUrl(url));
}
