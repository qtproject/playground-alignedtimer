/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the alignedtimer module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qalignedtimer.h"
#include "qalignedtimer_systemhb_p.h"
#include <QDebug>

#include <errno.h>
#include <stdio.h>

QTALIGNEDTIMER_BEGIN_NAMESPACE

QAlignedTimerPrivate::QAlignedTimerPrivate(QObject *parent)
    : QObject(parent)
    , m_lastError(QAlignedTimer::NoError)
    , m_minimumInterval(0)
    , m_maximumInterval(0)
    , m_running(false)
    , m_singleShot(false)
    , m_systemhbdHandler(0)
    , m_notifier(0)
{
    m_systemhbdHandler = systemhb_open();

    if (!m_systemhbdHandler) {
        m_lastError = QAlignedTimer::InternalError;
        qWarning() <<Q_FUNC_INFO <<"systemhb_open error" << m_systemhbdHandler<< errno <<strerror(errno);
        return;
    }

    int sockfd = systemhb_get_fd(m_systemhbdHandler);
    if (!(sockfd > -1)) {
        m_lastError = QAlignedTimer::InternalError;
        qWarning() <<Q_FUNC_INFO <<"socket failure"<<strerror(errno);
        return;
    }

    m_notifier = new QSocketNotifier(sockfd, QSocketNotifier::Read);
    if (!QObject::connect(m_notifier, SIGNAL(activated(int)), this, SLOT(heartbeatReceived(int)))) {
        delete m_notifier, m_notifier = 0;
        m_lastError = QAlignedTimer::TimerFailed;
        qWarning()<<Q_FUNC_INFO <<"timer failed";
        return;
    }
    m_notifier->setEnabled(false);
}

QAlignedTimerPrivate::~QAlignedTimerPrivate()
{
    if (m_systemhbdHandler)
        (void)systemhb_close(m_systemhbdHandler);

    if (m_notifier)
        delete m_notifier;
}

void QAlignedTimerPrivate::wokeUp()
{
    if (!m_running)
        return;

    if (!(m_systemhbdHandler && m_notifier)) {
        m_lastError = QAlignedTimer::InternalError;
        qWarning()<<Q_FUNC_INFO <<"internal error occured";
        return;
    }

    m_notifier->setEnabled(false);

    (void)systemhb_I_woke_up(m_systemhbdHandler);

    m_running = false;
    m_lastError = QAlignedTimer::NoError;

    if (!m_singleShot)
        start();
}

int QAlignedTimerPrivate::minimumInterval() const
{
    return m_minimumInterval;
}

void QAlignedTimerPrivate::setMinimumInterval(int seconds)
{
    m_minimumInterval = seconds;
}

int QAlignedTimerPrivate::maximumInterval() const
{
    return m_maximumInterval;
}

void QAlignedTimerPrivate::setMaximumInterval(int seconds)
{
    m_maximumInterval = seconds;
}

void QAlignedTimerPrivate::setSingleShot(bool singleShot)
{
    m_singleShot = singleShot;
}

bool QAlignedTimerPrivate::isSingleShot() const
{
    return m_singleShot;
}

void QAlignedTimerPrivate::singleShot(int minimumTime, int maximumTime, QObject *receiver, const char *member)
{
    if (receiver && member) {
        QAlignedTimerPrivate *alignedTimer = new QAlignedTimerPrivate(receiver);

        alignedTimer->m_singleShot = true;

        connect(alignedTimer, SIGNAL(timeout()), receiver, member);
        alignedTimer->start(minimumTime, maximumTime);
    }
}

QAlignedTimer::AlignedTimerError QAlignedTimerPrivate::lastError() const
{
    return m_lastError;
}

void QAlignedTimerPrivate::start(int minimumTime, int maximumTime)
{
    m_minimumInterval = minimumTime;
    m_maximumInterval = maximumTime;

    start();
}

void QAlignedTimerPrivate::start()
{
    if (m_running)
        return;

    if (!(m_systemhbdHandler && m_notifier)) {
        m_lastError = QAlignedTimer::InternalError;
        qWarning()<<Q_FUNC_INFO <<"internal error occured";
        return;
    }

    int mustWait = 0;
    time_t unixTime = systemhb_wait(m_systemhbdHandler, m_minimumInterval, m_maximumInterval, mustWait);

    if (unixTime == (time_t)-1) {
        m_lastError = QAlignedTimer::TimerFailed;
        qWarning()<<Q_FUNC_INFO <<"Timer failed";
        return;
    }

    m_notifier->setEnabled(true);
    m_running = true;
    m_lastError = QAlignedTimer::NoError;
}

void QAlignedTimerPrivate::stop()
{
    if (!m_running)
        return;

    if (!(m_systemhbdHandler && m_notifier)) {
        m_lastError = QAlignedTimer::InternalError;
        qWarning() <<Q_FUNC_INFO<< "systemhb_internal error";
        return;
    }

    m_notifier->setEnabled(false);

    (void)systemhb_discard_wakeups(m_systemhbdHandler);

    m_running = false;
    m_lastError = QAlignedTimer::NoError;
}

void QAlignedTimerPrivate::heartbeatReceived(int sock) {
    Q_UNUSED(sock);

    stop();
    emit timeout();

    if (!m_singleShot)
        start();
}

bool QAlignedTimerPrivate::isActive() const
{
    return m_running;
}

#include "moc_qalignedtimer_systemhb_p.cpp"

QTALIGNEDTIMER_END_NAMESPACE
