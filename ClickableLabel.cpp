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
	emit clicked(e->pos());
}
