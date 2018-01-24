#include "ClickableLineEdit.h"

ClickableLineEdit::ClickableLineEdit(QWidget* parent)
	: QLineEdit(parent)
{
}

void ClickableLineEdit::mouseReleaseEvent(QMouseEvent* e)
{
	if (e->button()!=Qt::LeftButton)
	{
		e->ignore();
		return;
	}

	e->accept();
	emit clicked(e->pos());
}
