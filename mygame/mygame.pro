#-------------------------------------------------
#
# Project created by QtCreator 2022-10-27T10:57:58
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
CONFIG += resources_big
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    mycamp.cpp \
    startfrom.cpp \
    route.cpp \
    mainwindow.cpp \
    leiwujie.cpp \
    wushaung.cpp \
    lskill.cpp \
    rolechoice.cpp \
    hanghao.cpp

HEADERS += \
    mycamp.h \
    startfrom.h \
    route.h \
    mainwindow.h \
    leiwujie.h \
    wushaung.h \
    lskill.h \
    rolechoice.h \
    hanghao.h

FORMS += \
    mainwindow.ui \
    mainwindow.ui \
    startfrom.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rec.qrc
