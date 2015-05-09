#-------------------------------------------------
#
# Project created by QtCreator 2015-05-04T16:32:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ConnectFourGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    strategy.cpp \
    judge.cpp \
    game.cpp \
    board.cpp \
    controller.cpp \
    point.cpp \
    setting_dialog.cpp \
    my_strategy_dialog.cpp

HEADERS  += mainwindow.h \
    strategy.h \
    point.h \
    judge.h \
    game.h \
    board.h \
    controller.h \
    setting_dialog.h \
    my_strategy_dialog.h

FORMS    += mainwindow.ui \
    board.ui \
    setting_dialog.ui \
    my_strategy_dialog.ui
