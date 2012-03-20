/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the alignedtimer module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qalignedtimer.h"
#include <QDebug>
#if defined(ALIGNEDTIMER_SYSTEMHB)
#include "qalignedtimer_systemhb_p.h"
#else
#include "qalignedtimer_stub_p.h"
#endif
QTALIGNEDTIMER_BEGIN_NAMESPACE

Q_GLOBAL_STATIC(QAlignedTimerPrivate, alignedTimerPrivate)

/*!
    \class QAlignedTimer
    \ingroup events
    \brief The QAlignedTimer class provides a service for applications to synchronize their activity.

    QAlignedTimer is a fuzzy timer that allows applications that must do periodic activity like
    after being in sleep mode a certain period, to synchronize their activities in the same window of time.

    For example send network "alive" messages at the same time (i.e. turn the wireless radio on at the same time).

    The service is not only for network-aware applications, it is for use by any applications
    that need to periodic wake-ups.

    The recommended use case is when app uses single-shot timer only: set mintime 0 for the first call
    'to jump to the train' and mintime > 0 after 1st wakeup.
    \sa QBasicTimer, QTimer, QTimerEvent, QObject::timerEvent(), Timers,
*/

/*!
    \fn void QAlignedTimer::timeout()

    This signal is emitted when the timer times out.
*/

/*!
    \enum QAlignedTimer::AlignedTimerError
    This enum describes the last known AlignedTimerError

    \value NoError                        No error.
    \value AlignedTimerNotSupported       The aligned timer is not support on this platform
    \value InvalidArgument                Interval arguments are invalid.
    \value TimerFailed                    General timer failure.
    \value InternalError                  Internal error.
*/

/*!
    Constructs a QAlignedTimer object with the given \a parent.
*/
QAlignedTimer::QAlignedTimer(QObject *parent)
    : QObject(parent)
{
    d = new QAlignedTimerPrivate(this);
    connect(d, SIGNAL(timeout()), this, SIGNAL(timeout()));
}

/*!
    Destructs the QAlignedTimer
*/
QAlignedTimer::~QAlignedTimer()
{
}

/*!
    Starts the timer with the minimal interval of \a minimumTime, and maximum interval \a maximumTime in seconds.

    This is not a guaranteed interval, and the timeout signal may be fired at any time,
    depending on other clients attached to this timer.

    In the case of minimalInterval of 0, it means 'wake me up when someone else is woken up'.

*/
void QAlignedTimer::start(int minimumTime, int maximumTime)
{
    if (minimumTime > maximumTime || maximumTime <= 0) {
        d->m_lastError = QAlignedTimer::InvalidArgument;
        qWarning()<<Q_FUNC_INFO <<"invalid arguments minimumTime and maximumTime";
        return;
    }
    d->start(minimumTime, maximumTime);
}

/*!
    Starts the alignedtimer if the minimumtime is greater than zero
    and maximumtime is greater than the minimumtime
*/
void QAlignedTimer::start()
{
    int minimumTime = minimumInterval();
    int maximumTime = maximumInterval();
    if ((minimumTime > maximumTime) || (maximumTime <= 0)) {
        d->m_lastError = QAlignedTimer::InvalidArgument;
        qWarning() <<Q_FUNC_INFO <<"invalid arguments minimumTime and maximumTime";
        return;
    }
    d->start();
}

/*!
    This should be called when the application wakes up via other means than QAlignedTimer timeout.

    Other applications that are in their wakeup window *may* be woken up. Single-shot timer is canceled,
    and reoccuring timer interval will restart.

*/
void QAlignedTimer::wokeUp()
{
    d->wokeUp();
}

/*!
    Stops this timer request.
*/
void QAlignedTimer::stop()
{
    d->stop();
}

/*!
    Set the timeout minimum interval to \a seconds in seconds that must be waited before timeout
    signal is emitted.

    Time in seconds that MUST be waited before timeout.
    Value 0 means 'wake me up when someboy else is woken'.

    mintime value 0 should be used with special care, as it may cause too frequent wakeups.
    It is recommended that the first wait (if possible) uses minimum value of 0 to
    "jump to the train" and minimum value > 0 after 1st wakeup
*/
void QAlignedTimer::setMinimumInterval(int seconds)
{
    d->setMinimumInterval(seconds);
}

/*!
    \property QAlignedTimer::minimumInterval
    \brief The timers's minimumInterval.

    Returns this current timer minimum interval.
*/
int QAlignedTimer::minimumInterval() const
{
    return d->minimumInterval();
}

/*!
    Set the timeout maximum interval to \a seconds the wait must end.

    Time in seconds when the wait MUST end. It is wise to have maxtime-mintime
    quite big so all users of this service get synced.
    For example if you preferred wait is 120 seconds, use minval 110 and maxval 130.

    max interval must be greater than min interval.
*/
void QAlignedTimer::setMaximumInterval(int seconds)
{
    d->setMaximumInterval(seconds);
}

/*!
    \property QAlignedTimer::maximumInterval
    \brief The timer's maximumInterval.

    Returns this current timer maximum interval.
*/
int QAlignedTimer::maximumInterval() const
{
    return d->maximumInterval();
}

/*!
    Sets this timer to be a single shot \a singleShot is true, otherwise false.
*/
void QAlignedTimer::setSingleShot(bool singleShot)
{
    d->setSingleShot(singleShot);
}

/*!
    This static function starts a timer to call a slot after a \a minimumTime
    interval has elapsed, and ensures that it will be called before the
    \a maximumTime has elapsed.

    These values are specified in seconds.

    The receiver is the \a receiver object and the \a member is the slot.
*/
void QAlignedTimer::singleShot(int minimumTime, int maximumTime, QObject *receiver, const char *member)
{
    if (minimumTime > maximumTime || maximumTime <= 0)
        return;
    QAlignedTimerPrivate::singleShot(minimumTime, maximumTime, receiver, member);
}

/*!
    \property QAlignedTimer::singleShot
    Whether the timer is single shot.
*/

/*!
    Returns true if this timer is a single shot, otherwise false.
*/
bool QAlignedTimer::isSingleShot() const
{
    return d->isSingleShot();
}

/*!
    Returns the last AlignedTimerError.
*/
QAlignedTimer::AlignedTimerError QAlignedTimer::lastError() const
{
    return d->lastError();
}

/*!
    \property QAlignedTimer::active
    Returns true if the timer is running; otherwise false.
*/

/*!
    Returns true if the timer is running; otherwise false.
*/
bool QAlignedTimer::isActive () const
{
    return d->isActive();
}

#include "moc_qalignedtimer.cpp"

QTALIGNEDTIMER_END_NAMESPACE
