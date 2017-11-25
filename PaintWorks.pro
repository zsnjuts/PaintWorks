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


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    Area.cpp \
    Circle.cpp \
    CircleControl.cpp \
    CompFigure.cpp \
    Ellipse.cpp \
    EllipseControl.cpp \
    Figure.cpp \
    FigureControl.cpp \
    Line.cpp \
    LineControl.cpp \
    Point.cpp \
    Polygon.cpp \
    PolygonControl.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    Area.h \
    Circle.h \
    CircleControl.h \
    CompFigure.h \
    Ellipse.h \
    EllipseControl.h \
    Figure.h \
    FigureControl.h \
    Line.h \
    LineControl.h \
    Point.h \
    Polygon.h \
    PolygonControl.h

FORMS    += mainwindow.ui
