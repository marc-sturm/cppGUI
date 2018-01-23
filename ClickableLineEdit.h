#ifndef CLICKABLELineEdit_H
#define CLICKABLELineEdit_H

#include "cppGUI_global.h"
#include <QLineEdit>
#include <QMouseEvent>

///LineEdit with clicked(QPoint) event.
class CPPGUISHARED_EXPORT ClickableLineEdit
		: public QLineEdit
{
	Q_OBJECT

public:
	ClickableLineEdit(QWidget* parent = 0);
	void mouseReleaseEvent(QMouseEvent* event);

signals:
	void clicked(QPoint pos);
};

#endif // CLICKABLELineEdit_H
