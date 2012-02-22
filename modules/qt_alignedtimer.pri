QT.alignedtimer.VERSION = 5.0.0
QT.alignedtimer.MAJOR_VERSION = 5
QT.alignedtimer.MINOR_VERSION = 0
QT.alignedtimer.PATCH_VERSION = 0

QT.alignedtimer.name = QtAlignedTimer
QT.alignedtimer.bins = $$QT_MODULE_BIN_BASE
QT.alignedtimer.includes = $$QT_MODULE_INCLUDE_BASE $$QT_MODULE_INCLUDE_BASE/QtAlignedTimer
QT.alignedtimer.private_includes = $$QT_MODULE_INCLUDE_BASE/QtAlignedTimer/$$QT.alignedtimer.VERSION
QT.alignedtimer.sources = $$QT_MODULE_BASE/src/alignedtimer
QT.alignedtimer.libs = $$QT_MODULE_LIB_BASE
QT.alignedtimer.depends = core
QT.alignedtimer.DEFINES = QT_ALIGNEDTIMER_LIB

QT_CONFIG += alignedtimer
