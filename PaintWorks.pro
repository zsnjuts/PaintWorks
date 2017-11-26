#-------------------------------------------------
#
# Project created by QtCreator 2017-11-24T19:57:17
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PaintWorks
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    Figure.cpp \
    FigureControl.cpp \
    Line.cpp \
    LineControl.cpp \
    Point.cpp \
    Circle.cpp \
    CircleControl.cpp \
    Area.cpp \
    Ellipse.cpp \
    EllipseControl.cpp \
    Polygon.cpp \
    PolygonControl.cpp \
    CompFigure.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    Figure.h \
    FigureControl.h \
    Line.h \
    LineControl.h \
    Point.h \
    CircleControl.h \
    Circle.h \
    Area.h \
    Ellipse.h \
    EllipseControl.h \
    Polygon.h \
    PolygonControl.h \
    CompFigure.h

FORMS    += mainwindow.ui
