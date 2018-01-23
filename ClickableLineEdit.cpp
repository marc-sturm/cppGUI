#include "ClickableLineEdit.h"

ClickableLineEdit::ClickableLineEdit(QWidget* parent)
	: QLineEdit(parent)
{
}

void ClickableLineEdit::mouseReleaseEvent(QMouseEvent* event)
{
	emit clicked(event->pos());
}
