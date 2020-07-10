QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Client.cpp \
    Listen.cpp \
    chatmessage.cpp \
    chatmessage/qnchatmessage.cpp \
    friendlist.cpp \
    main.cpp \
    login.cpp \
    muitemdelegate.cpp \
    register.cpp

HEADERS += \
    Client.h \
    baohan.h \
    chatmessage.h \
    chatmessage/qnchatmessage.h \
    friendlist.h \
    login.h \
    muitemdelegate.h \
    register.h \
    stdafx.h

FORMS += \
    chatmessage.ui \
    friendlist.ui \
    login.ui \
    register.ui

#INCLUDEPATH += E:\QT Creator\build-untitled4-Desktop_x86_windows_msvc2019_pe_64bit-Debug\debug

#LIBS += \E:\QT Creator\build-untitled4-Desktop_x86_windows_msvc2019_pe_64bit-Debug\debug\sqlite3.lib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Demo_MessageChat/img/Customer Copy.png \
    ../Demo_MessageChat/img/Customer Copy.png \
    ../TrainingProject-master/InstantMessaging/Qt/MuListView/images/Customer Copy.png \
    ../TrainingProject-master/InstantMessaging/Qt/MuListView/images/Customer Copy.png \
    ../TrainingProject-master/InstantMessaging/Qt/MuListView/images/Customer Copy.png \
    Customer Copy.png \
    Customer Copy.png \
    img/Customer Copy.png \
    img/Customer Copy.png \
    img/Customer Copy.png \
    img/Customer Copy.png

RESOURCES += \
    ../TrainingProject-master/InstantMessaging/Qt/MuListView/Style.qrc \
    ../TrainingProject-master/InstantMessaging/Qt/MuListView/imgs.qrc
