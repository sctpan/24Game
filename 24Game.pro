#-------------------------------------------------
#
# Project created by QtCreator 2017-10-30T11:31:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 24Game
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    menu.cpp \
    solologin.cpp \
    register.cpp \
    rank.cpp \
    userinfo.cpp \
    instruction.cpp \
    mkcontest.cpp \
    regcontest.cpp \
    contestwindow.cpp

HEADERS += \
        mainwindow.h \
    menu.h \
    solologin.h \
    register.h \
    rank.h \
    userinfo.h \
    instruction.h \
    mkcontest.h \
    regcontest.h \
    contestwindow.h

FORMS += \
    menu.ui \
    solologin.ui \
    mainwindow.ui \
    register.ui \
    rank.ui \
    instruction.ui \
    mkcontest.ui \
    regcontest.ui \
    contestwindow.ui

RESOURCES += \
    resource.qrc
