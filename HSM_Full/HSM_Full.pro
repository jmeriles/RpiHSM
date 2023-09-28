#-------------------------------------------------
#
# Project created by QtCreator 2021-11-22T12:08:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HSM_Full
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

CONFIG += c++11
CONFIG += qwt
CONFIG += console

SOURCES += \
        crc.cpp \
        customelement.cpp \
        hybridel.cpp \
        interlock.cpp \
        lowpassfilter2.cpp \
        main.cpp \
        hsm_full.cpp\
        ABE_ExpanderPi.cpp \
        psas.cpp \
        spancalibration.cpp

HEADERS += \
        hsm_full.h \
        lowpassfilter2.h

FORMS += \
        customelement.ui \
        hsm_full.ui \
        hybridel.ui \
        interlock.ui \
        psas.ui \
        spancalibration.ui

INCLUDEPATH += \
        /home/pi/Desktop/HSM \
        /usr/lib/python3.9/config-3.7-arm-linux-gnueabihf\
        /usr/lib\
        /usr/include/python3.9 \



LIBS += -L"/usr/lib/arm-linux-gnueabihf" -lpython3.9\



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_DEFAULT_INCDIRS=//


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lwiringPi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lwiringPi
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lwiringPi

INCLUDEPATH += $$PWD/../../../../usr/include
DEPENDPATH += $$PWD/../../../../usr/include

DISTFILES +=



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/qwt-6.2.0/lib/release/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/qwt-6.2.0/lib/debug/ -lqwt
else:unix: LIBS += -L$$PWD/../../../../../usr/local/qwt-6.2.0/lib/ -lqwt

INCLUDEPATH += $$PWD/../../../../../usr/local/qwt-6.2.0/include
DEPENDPATH += $$PWD/../../../../../usr/local/qwt-6.2.0/include



INCLUDEPATH += $$PWD/../../../../../
DEPENDPATH += $$PWD/../../../../../





win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libcrc-2.0/lib/release/ -lcrc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libcrc-2.0/lib/debug/ -lcrc
else:unix: LIBS += -L$$PWD/libcrc-2.0/lib/ -lcrc

INCLUDEPATH += $$PWD/libcrc-2.0/include
DEPENDPATH += $$PWD/libcrc-2.0/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libcrc-2.0/lib/release/libcrc.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libcrc-2.0/lib/debug/libcrc.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libcrc-2.0/lib/release/crc.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libcrc-2.0/lib/debug/crc.lib
else:unix: PRE_TARGETDEPS += $$PWD/libcrc-2.0/lib/libcrc.a
