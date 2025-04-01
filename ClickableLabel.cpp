#include "ClickableLabel.h"

ClickableLabel::ClickableLabel(QWidget* parent)
	: QLabel(parent)
{
}

void ClickableLabel::mouseReleaseEvent(QMouseEvent* e)
{
	if (e->button()!=Qt::LeftButton)
	{
		e->ignore();
		return;
	}

	e->accept();
    #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    emit clicked(e->globalPosition().toPoint());
    #else
    emit clicked(e->globalPos());
    #endif
}
