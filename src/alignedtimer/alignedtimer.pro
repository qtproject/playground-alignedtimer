load(qt_module)

TARGET = QtAlignedTimer
QPRO_PWD = $PWD
CONFIG += module
MODULE_PRI = ../../modules/qt_alignedtimer.pri

QT = core

DEFINES += QT_BUILD_ALIGNEDTIMER_LIB QT_MAKEDLL

load(qt_module_config)
VERSION = $$QT.alignedtimer.VERSION


PUBLIC_HEADERS += \
    qalignedtimer.h \
    qalignedtimerglobal.h


SOURCES += \
    qalignedtimer.cpp

            # alignedtimer for systemhb
            contains(systemhb_enabled, yes): {
                SOURCES += qalignedtimer_systemhb.cpp
                HEADERS += qalignedtimer_systemhb_p.h
                PKGCONFIG += libsystemhb
                DEFINES += ALIGNEDTIMER_SYSTEMHB
                LIBS += -lsystemhb
            } else {
                SOURCES += qalignedtimer_stub.cpp
                HEADERS += qalignedtimer_stub_p.h
            }

HEADERS += qtalignedtimerversion.h $$PUBLIC_HEADERS $$PRIVATE_HEADERS
