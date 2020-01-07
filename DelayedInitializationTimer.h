#ifndef DELAYEDINITIALIZATIONTIMER_H
#define DELAYEDINITIALIZATIONTIMER_H

#include "cppGUI_global.h"
#include<QWidget>
#include<QTimer>

//Timer that triggers initialization of a Widget once it's shown
class CPPGUISHARED_EXPORT DelayedInitializationTimer
	: public QObject
{
	Q_OBJECT

public:
	//Constructor. If 'auto_connect' is enabled, the slot 'delayedInitialization()' of the 'client' is triggered.
	DelayedInitializationTimer(QWidget* client, bool auto_connect);

signals:
	//Signal that is triggered once the client widget is shown
	void triggerInitialization();

private slots:
	void check();

private:
	QWidget* client_;
	QTimer timer_;
};

#endif // DELAYEDINITIALIZATIONTIMER_H
