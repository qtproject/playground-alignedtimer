/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the test suite of the Qt Toolkit.
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

#include <QtTest/QtTest>
#include <qalignedtimer.h>
QTALIGNEDTIMER_USE_NAMESPACE
Q_DECLARE_METATYPE(QAlignedTimer::AlignedTimerError);

static bool waitForSignal(QObject *obj, const char *signal, int timeout = 0)
{
    QEventLoop loop;
    QObject::connect(obj, signal, &loop, SLOT(quit()));
    QTimer timer;
    QSignalSpy timeoutSpy(&timer, SIGNAL(timeout()));
    if (timeout > 0) {
        QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        timer.setSingleShot(true);
        timer.start(timeout);
    }
    loop.exec();
    return timeoutSpy.isEmpty();
}

class tst_QAlignedTimer : public QObject
{

    Q_OBJECT

public:
    tst_QAlignedTimer();
    virtual ~tst_QAlignedTimer();

private slots:
    void initTestCase();

    void tst_wokeUp();

    void tst_minimumInterval();
    void tst_maximumInterval();

    void tst_setSingleShot();
    void tst_isSingleShot() ;

    void tst_singleShot();

    void tst_lastError();

    void tst_start();
    void tst_stop();

public Q_SLOTS:
    void timeout();

private:
    QAlignedTimer alignedtime2r;

};

tst_QAlignedTimer::tst_QAlignedTimer()
{
}

tst_QAlignedTimer::~tst_QAlignedTimer()
{
}

void tst_QAlignedTimer::initTestCase()
{
   qRegisterMetaType<QAlignedTimer::AlignedTimerError>("QAlignedTimer::AlignedTimerError");
}

void tst_QAlignedTimer::tst_wokeUp()
{
    QAlignedTimer alignedtimer;
    if (alignedtimer.lastError() == QAlignedTimer::AlignedTimerNotSupported) {
        QSKIP("This test not supported on this platform");
    }
    alignedtimer.setSingleShot(true);
    alignedtimer.start(8,10);

    QVERIFY(alignedtimer.isActive());

    alignedtimer.wokeUp();
    QVERIFY(!alignedtimer.isActive());
}

void tst_QAlignedTimer::tst_minimumInterval()
{
    QAlignedTimer alignedtimer;
    if (alignedtimer.lastError() == QAlignedTimer::AlignedTimerNotSupported) {
        QSKIP("This test not supported on this platform");
    }
    alignedtimer.setMinimumInterval(0);
    QVERIFY(alignedtimer.minimumInterval() == 0);
    alignedtimer.setMinimumInterval(10);
    QVERIFY(alignedtimer.minimumInterval() == 10);

    alignedtimer.setMinimumInterval(-1);
    alignedtimer.start();
    QVERIFY(alignedtimer.lastError() == QAlignedTimer::InvalidArgument);
}

void tst_QAlignedTimer::tst_maximumInterval()
{

    QAlignedTimer alignedtimer;
    if (alignedtimer.lastError() == QAlignedTimer::AlignedTimerNotSupported) {
        QSKIP("This test not supported on this platform");
    }

    alignedtimer.setMinimumInterval(0);
    alignedtimer.setMaximumInterval(0);
    QVERIFY(alignedtimer.maximumInterval() == 0);

    alignedtimer.setMaximumInterval(11);
    QVERIFY(alignedtimer.maximumInterval() == 11);

    alignedtimer.setMaximumInterval(-1);
    alignedtimer.start();
    QVERIFY(alignedtimer.lastError() == QAlignedTimer::InvalidArgument);
}

void tst_QAlignedTimer::tst_setSingleShot()
{
    QAlignedTimer alignedtimer;
    if (alignedtimer.lastError() == QAlignedTimer::AlignedTimerNotSupported) {
        QSKIP("This test not supported on this platform");
    }
    alignedtimer.setSingleShot(true);
    QVERIFY(alignedtimer.isSingleShot());
    alignedtimer.setSingleShot(false);
    QVERIFY(!alignedtimer.isSingleShot());
}

void tst_QAlignedTimer::tst_isSingleShot()
{
    QAlignedTimer alignedtimer;
    if (alignedtimer.lastError() == QAlignedTimer::AlignedTimerNotSupported) {
        QSKIP("This test not supported on this platform");
    }
    alignedtimer.setSingleShot(true);
    QVERIFY(alignedtimer.isSingleShot());
    alignedtimer.setSingleShot(false);
    QVERIFY(!alignedtimer.isSingleShot());
}

void tst_QAlignedTimer::tst_singleShot()
{
    QAlignedTimer alignedtimer;
    if (alignedtimer.lastError() == QAlignedTimer::AlignedTimerNotSupported) {
        QSKIP("This test not supported on this platform");
    }

    alignedtimer.setSingleShot(true);
    alignedtimer.start(2,3);
    QVERIFY(alignedtimer.isActive());
    QVERIFY(::waitForSignal(&alignedtimer, SIGNAL(timeout()), 4 * 1000));
    QVERIFY(!alignedtimer.isActive());

    alignedtimer.setSingleShot(false);
    alignedtimer.start(2,3);
    QVERIFY(alignedtimer.isActive());
    QVERIFY(::waitForSignal(&alignedtimer, SIGNAL(timeout()), 4 * 1000));
    QVERIFY(alignedtimer.isActive());
}

void tst_QAlignedTimer::tst_lastError()
{
    QAlignedTimer alignedtimer;
    if (alignedtimer.lastError() == QAlignedTimer::AlignedTimerNotSupported) {
        QSKIP("This test not supported on this platform");
    }
}

void tst_QAlignedTimer::tst_start()
{
    QAlignedTimer alignedtimer;
    if (alignedtimer.lastError() == QAlignedTimer::AlignedTimerNotSupported) {
        QSKIP("This test not supported on this platform");
    }


    alignedtimer.start(8,10);
    QVERIFY(alignedtimer.isActive());
    alignedtimer.stop();
    alignedtimer.setMinimumInterval(8);
    alignedtimer.setMaximumInterval(10);
    alignedtimer.start();
    QVERIFY(alignedtimer.isActive());

    alignedtime2r.start(2,3);
    QVERIFY(alignedtime2r.isActive());
    QVERIFY(::waitForSignal(&alignedtime2r, SIGNAL(timeout()), 5 * 1000));
    QVERIFY(alignedtime2r.isActive());

    QAlignedTimer alignedtimer2;
    alignedtimer2.setMinimumInterval(11);
    alignedtimer2.setMaximumInterval(10);
    alignedtimer2.start();
    QVERIFY(alignedtimer2.lastError() == QAlignedTimer::InvalidArgument);
    QVERIFY(!alignedtimer2.isActive());

    QAlignedTimer alignedtimer3;
    alignedtimer3.start(11,10);
    QVERIFY(alignedtimer3.lastError() == QAlignedTimer::InvalidArgument);
    QVERIFY(!alignedtimer3.isActive());

    QAlignedTimer alignedtimer4;
    alignedtimer4.start(10,0);
    QVERIFY(alignedtimer4.lastError() == QAlignedTimer::InvalidArgument);
    QVERIFY(!alignedtimer4.isActive());

}

void tst_QAlignedTimer::tst_stop()
{
    QAlignedTimer alignedtimer;
    if (alignedtimer.lastError() == QAlignedTimer::AlignedTimerNotSupported) {
        QSKIP("This test not supported on this platform");
    }
    alignedtimer.start(8,10);
    alignedtimer.stop();
    QVERIFY(!alignedtimer.isActive());

    alignedtimer.start();
    alignedtimer.stop();
    QVERIFY(!alignedtimer.isActive());

    alignedtimer.setSingleShot(true);
    alignedtimer.start();
    alignedtimer.stop();
    QVERIFY(!alignedtimer.isActive());

    alignedtimer.start();
    alignedtimer.stop();
    QVERIFY(!alignedtimer.isActive());
}

void tst_QAlignedTimer::timeout()
{
    QVERIFY(!alignedtime2r.isActive());
}

QTEST_MAIN(tst_QAlignedTimer)
#include "tst_qalignedtimer.moc"
