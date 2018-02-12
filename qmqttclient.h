#ifndef QMQTTCLIENT_H
#define QMQTTCLIENT_H

#include "qmqtt\qmqtt.h"
#include <QLoggingCategory>
#include <QHostAddress>
#include <QUuid>

enum QosLevel {
    QOS_0 = 0,
    QOS_1 = 1,
    QOS_2 = 2
};

class QMqttClient : public QMQTT::Client
{

    Q_OBJECT

public:

    QMqttClient();

    // Set and return client name
    // defaults to GUUID name if not supplied
    void setName(QString name);
    QString name() { return _name; }

    // Manipulate Message sent when client
    // connects to broker
    void setOnlineMessagePayload(const QString message);
    QString onlineMessagePayload() { return _onlineMessagePayload; }
    void setOnlineMessageTopic(const QString topic);
    QString onlineMessageTopic() { return _onlineMessageTopic; }
    void setOnlineMessageRetain(bool value) { _onlineMessageRetain = value; }
    bool onlineMessageRetain() { return _onlineMessageRetain; }

    // convenience methods
    void publish(const char *topic, const char *message, QosLevel qos = QOS_0, bool retain = false);
    void publish(const char *topic, QString message, QosLevel qos = QOS_0, bool retain = false);
    void publish(QString topic, const char *message, QosLevel qos = QOS_0, bool retain = false);
    void publish(QString topic, QString message, QosLevel qos = QOS_0, bool retain = false);

    void setHost(const char *host);

    QString uuid() { return _uuid; }

    // what are these?
    void onMqttConnect();
    void onMqttDisconnect();

protected:

    QString _name;
    QString _uuid;
    quint16 _id; // what is this?

    QString _onlineMessagePayload;
    QString _onlineMessageTopic;
    bool _onlineMessageRetain;

public slots:

    void on_connected();
    void on_disconnected();

    void on_messageReceived(QMQTT::Message);

};



#endif // QMQTTCLIENT_H
