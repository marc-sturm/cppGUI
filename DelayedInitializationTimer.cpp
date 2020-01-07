#include "DelayedInitializationTimer.h"
#include <QDateTime>
#include <QDebug>

DelayedInitializationTimer::DelayedInitializationTimer(QWidget* client, bool auto_connect)
	: QObject()
	, client_(client)
	, timer_()
{
	//start timer
	connect(&timer_, SIGNAL(timeout()), this, SLOT(check()));
	timer_.setSingleShot(false);
	timer_.start(50);

	//connect
	if (auto_connect)
	{
		connect(this, SIGNAL(triggerInitialization()), client_, SLOT(delayedInitialization()));
	}
}

void DelayedInitializationTimer::check()
{
	if (!timer_.isActive()) return;
	if (!client_->isVisible()) return;

	timer_.stop();
	emit triggerInitialization();
}
