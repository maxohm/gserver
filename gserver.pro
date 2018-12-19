#-------------------------------------------------
#
# Project created by QtCreator 2018-12-19T19:43:09
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4) {
QT += widgets network
DEFINES += HAVE_QT5
} else {
QT += core gui network qt3support
}

TARGET = gserver
TEMPLATE = app


SOURCES += main.cpp\
        gserver.cpp \
    ../gclient/msock.cpp

HEADERS  += gserver.h \
    ../gclient/msock.h

FORMS    += gserver.ui

INCLUDEPATH += ../gclient/
