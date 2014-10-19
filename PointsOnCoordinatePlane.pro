#-------------------------------------------------
#
# Project created by QtCreator 2014-10-18T16:45:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = PointsOnCoordinatePlane
TEMPLATE = app


SOURCES += main.cpp\
        Dialog.cpp \
    QCustomPlot.cpp

HEADERS  += Dialog.h \
    QCustomPlot.h

FORMS    += Dialog.ui
