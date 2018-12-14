#-------------------------------------------------
#
# Project created by QtCreator 2018-06-19T11:07:02
#
#-------------------------------------------------

QT       += core gui sql
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PictureMain
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp\
    showwidget.cpp \
    utils.cpp \
    pixitem.cpp \
    dialognoreduce.cpp \
    recentopened.cpp \
    yuchuli.cpp \
    histogram.cpp \
    fenge.cpp \
    laserwelddlg.cpp \
    arcdlg.cpp \
    adduserdlg.cpp \
    recorddlg.cpp \
    datamanager.cpp \
    createdb.cpp \
    usermanager.cpp \
    arcmanager.cpp \
    imagemanager.cpp \
    processmanager.cpp \
    ca.cpp \
    quanju.cpp


HEADERS  +=mainwindow.h\
    showwidget.h \
    utils.h \
    pixitem.h \
    dialognoreduce.h \
    recentopened.h \
    yuchuli.h \
    histogram.h \
    fenge.h \
    laserwelddlg.h \
    arcdlg.h \
    adduserdlg.h \
    recorddlg.h \
    datamanager.h \
    createdb.h \
    usermanager.h \
    arcmanager.h \
    imagemanager.h \
    processmanager.h \
    ca.h \
    quanju.h


INCLUDEPATH += D:\ruanjian\opencv\opencv\build\include\opencv2 \
               D:\ruanjian\opencv\opencv\build\include\opencv\
               D:\ruanjian\opencv\opencv\build\include

LIBS += D:\ruanjian\install/x86/mingw/lib/libopencv_*

FORMS += \
    dialognoreduce.ui \
    mainwindow.ui \
    laserwelddlg.ui \
    arcdlg.ui \
    adduserdlg.ui \
    recorddlg.ui \
    datamanager.ui \
    usermanager.ui \
    arcmanager.ui \
    imagemanager.ui \
    processmanager.ui

RESOURCES += \
    ziyuan.qrc
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Depends/win32/vs2013shared/ -lMVSDKm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Depends/win32/vs2013shared/ -lMVSDKmd
else:unix: LIBS += -L$$PWD/Depends/win32/vs2013shared/ -lMVSDKm

INCLUDEPATH += $$PWD/Depends/win32/vs2013shared
DEPENDPATH += $$PWD/Depends/win32/vs2013shared

INCLUDEPATH += $$PWD/Include/GenICam/CAPI
DEPENDPATH += $$PWD/Include/GenICam/CAPI
