#-------------------------------------------------
#
# Project created by QtCreator 2017-01-29T21:44:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts core serialport

TARGET = m2ems
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES +=

DISTFILES += \
    img/bas_adm.jpg \
    img/bas_comp.jpg \
    img/bas_det.jpg \
    img/bas_ech.jpg \
    img/haut_adm.jpg \
    img/haut_comp.jpg \
    img/haut_det.jpg \
    img/haut_ech.jpg \
    img/milieu_adm.jpg \
    img/milieu_comp.jpg \
    img/milieu_det.jpg \
    img/milieu_ech.jpg
