QT += core network

INCLUDEPATH += $$PWD

DEFINES += QMQTT_LIBRARY
include(qmqtt/qmqtt.pri)

HEADERS += \
    $$PWD/qmqttclient.h

SOURCES += \
    $$PWD/qmqttclient.cpp
