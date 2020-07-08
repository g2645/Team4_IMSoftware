QT       += core gui

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
    chatmessage.cpp \
    friendlist.cpp \
    main.cpp \
    login.cpp \
    muitemdelegate.cpp \
    register.cpp

HEADERS += \
    chatmessage.h \
    friendlist.h \
    login.h \
    muitemdelegate.h \
    register.h

FORMS += \
    chatmessage.ui \
    friendlist.ui \
    login.ui \
    register.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../TrainingProject-master/InstantMessaging/Qt/MuListView/images/HotDog.jpg \
    ../TrainingProject-master/InstantMessaging/Qt/MuListView/images/PACT.jpg \
    ../TrainingProject-master/InstantMessaging/Qt/MuListView/images/li.jpg \
    ../TrainingProject-master/InstantMessaging/Qt/MuListView/images/logo.jpg \
    ../TrainingProject-master/InstantMessaging/Qt/MuListView/images/yang.jpg \
    ../TrainingProject-master/InstantMessaging/Qt/MuListView/images/zhang.jpg \
    ../TrainingProject-master/InstantMessaging/Qt/MuListView/style.qss

RESOURCES += \
    ../TrainingProject-master/InstantMessaging/Qt/MuListView/Style.qrc \
    ../TrainingProject-master/InstantMessaging/Qt/MuListView/imgs.qrc
