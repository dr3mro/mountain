#-------------------------------------------------
#
# Project created by QtCreator 2018-11-09T16:57:45
#
#-------------------------------------------------

QT       += core gui network concurrent
CONFIG+=sdk_no_version_check
CONFIG += c++14
CONFIG += app_bundle
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
ICON = icon.icns
TARGET = Mountain
TEMPLATE = app
QMAKE_INFO_PLIST = Info.plist
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    menu.cpp \
    trayicon.cpp \
    kernel.cpp \
    guiserver.cpp \
    settings.cpp

HEADERS += \
    menu.h \
    trayicon.h \
    kernel.h \
    guiserver.h \
    settings.h

FORMS +=

RESOURCES += \
    resources.qrc

DISTFILES +=
