#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include "cppGUI_global.h"
#include <QLabel>
#include <QMouseEvent>

///Label with clicked(QPoint) event.
class CPPGUISHARED_EXPORT ClickableLabel
		: public QLabel
{
	Q_OBJECT

public:
	ClickableLabel(QWidget* parent = 0);

protected:
	void mouseReleaseEvent(QMouseEvent* event);

signals:
	///Signal that is emitted when the label is clicked - the position is global!
	void clicked(QPoint pos);
};

#endif // CLICKABLELABEL_H
