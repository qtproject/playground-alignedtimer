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
#include "qalignedtimer_stub_p.h"

QTALIGNEDTIMER_BEGIN_NAMESPACE

QAlignedTimerPrivate::QAlignedTimerPrivate(QObject *parent)
    : QObject(parent)
{
}

QAlignedTimerPrivate::~QAlignedTimerPrivate()
{
}

void QAlignedTimerPrivate::wokeUp()
{
}

int QAlignedTimerPrivate::minimumInterval() const
{
    return -1;
}

void QAlignedTimerPrivate::setMinimumInterval(int seconds)
{
    Q_UNUSED(seconds);
}

int QAlignedTimerPrivate::maximumInterval() const
{
    return -1;
}

void QAlignedTimerPrivate::setMaximumInterval(int seconds)
{
    Q_UNUSED(seconds);
}

void QAlignedTimerPrivate::setSingleShot(bool singleShot)
{
    Q_UNUSED(singleShot);
}

bool QAlignedTimerPrivate::isSingleShot() const
{
    return false;
}

void QAlignedTimerPrivate::singleShot(int minimumTime, int maximumTime, QObject *receiver, const char *member)
{
    Q_UNUSED(minimumTime);
    Q_UNUSED(maximumTime);
    Q_UNUSED(receiver);
    Q_UNUSED(member);
}

QAlignedTimer::AlignedTimerError QAlignedTimerPrivate::lastError() const
{
    return QAlignedTimer::AlignedTimerNotSupported;
}

void QAlignedTimerPrivate::start(int minimumTime, int maximumTime)
{
    Q_UNUSED(minimumTime);
    Q_UNUSED(maximumTime);
}

void QAlignedTimerPrivate::start()
{
}

void QAlignedTimerPrivate::stop()
{
}

bool QAlignedTimerPrivate::isActive () const
{
    return false;
}

#include "moc_qalignedtimer_stub_p.cpp"

QTALIGNEDTIMER_END_NAMESPACE
