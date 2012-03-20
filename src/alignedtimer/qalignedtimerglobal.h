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

#ifndef QTALIGNEDTIMERGLOBAL_H
#define QTALIGNEDTIMERGLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QT_NAMESPACE)
#  define QTALIGNEDTIMER_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::QtAlignedTimer::name
#  define QTALIGNEDTIMER_BEGIN_NAMESPACE namespace QT_NAMESPACE { namespace QtAlignedTimer {
#  define QTALIGNEDTIMER_END_NAMESPACE } }
#  define QTALIGNEDTIMER_USE_NAMESPACE using namespace QT_NAMESPACE; using namespace QtAlignedTimer;
#else
#  define QTALIGNEDTIMER_PREPEND_NAMESPACE(name) ::QtAlignedTimer::name
#  define QTALIGNEDTIMER_BEGIN_NAMESPACE namespace QtAlignedTimer {
#  define QTALIGNEDTIMER_END_NAMESPACE }
#  define QTALIGNEDTIMER_USE_NAMESPACE using namespace QtAlignedTimer;
#endif

#if !defined(Q_ALIGNEDTIMER_EXPORT)
#  if defined(QT_SHARED)
#    define Q_ALIGNEDTIMER_EXPORT Q_DECL_EXPORT
#  else
#    define Q_ALIGNEDTIMER_EXPORT
#  endif
#endif

#define QTALIGNEDTIMER_VERSION_NAME "org.qt-project.Qt.alignedtimer.api.version"
#define QTALIGNEDTIMER_IMPLEMENTATION_VERSION_NAME "org.qt-project.Qt.alignedtimer.implementation.version"
#define QTALIGNEDTIMER_VERSION 1

#endif
