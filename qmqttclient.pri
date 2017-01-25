QT += core network

INCLUDEPATH += $$PWD

DEFINES += QT_BUILD_MQTT_LIB

include(qmqtt/src/mqtt/mqtt.pri)

HEADERS += \
    $$PWD/qmqttclient.h

SOURCES += \
    $$PWD/qmqttclient.cpp
