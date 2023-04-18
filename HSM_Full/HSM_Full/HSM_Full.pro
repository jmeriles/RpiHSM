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
        customelement.cpp \
        hybridel.cpp \
        main.cpp \
        hsm_full.cpp\
        ABE_ExpanderPi.cpp \
        psas.cpp

HEADERS += \
        hsm_full.h

FORMS += \
        customelement.ui \
        hsm_full.ui \
        hybridel.ui \
        psas.ui

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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../pigpio-master/release/ -lpigpiod_if2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../pigpio-master/debug/ -lpigpiod_if2
else:unix: LIBS += -L$$PWD/../../../pigpio-master/ -lpigpiod_if2

INCLUDEPATH += $$PWD/../../../pigpio-master
DEPENDPATH += $$PWD/../../../pigpio-master

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/release/ -lwiringPi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/debug/ -lwiringPi
else:unix: LIBS += -L$$PWD/../../../../../usr/lib/ -lwiringPi

INCLUDEPATH += $$PWD/../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../usr/include

DISTFILES +=
