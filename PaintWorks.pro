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
    CompFigure.cpp \
    SimpleFigure.cpp \
    CutWindow.cpp \
    gl3dwidget.cpp

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
    CompFigure.h \
    SimpleFigure.h \
    CutWindow.h \
    gl3dwidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    paintworks_resource.qrc

RC_FILE += paintworks.rc

QMAKE_CXXFLAGS += -Wno-sign-compare
