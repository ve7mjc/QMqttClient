#include "qmqttclient.h"

QMqttClient::QMqttClient()
    : QMQTT::Client()
{

    // Disable the QMQTT noisy logging output
    QLoggingCategory::setFilterRules("*.*=false");

    // Create a unique GUUID for this client
    // to prevent collisions
    // TODO: add persistence
    QUuid uuid = QUuid::createUuid();
    _uuid = uuid.toString();

    // set the client name to the UUID
    // which may be overridden post-constructor
    _name = _uuid;

    connect(this, SIGNAL(connected()),
                     this, SLOT(on_connected()));

    connect(this, SIGNAL(disconnected()),
                     this, SLOT(on_disconnected()));

    connect(this, SIGNAL(received(QMQTT::Message)),
                     this, SLOT(on_messageReceived(QMQTT::Message)));

    // decent defaults (tm)
    setHost("172.23.0.17");
    setPort(1883);
    _onlineMessageTopic = QString("client/%1/status").arg(_name);
    _onlineMessagePayload = "online";

    // default to auto-reconnect - why not?
    setAutoReconnect(true);
}



// Publish Convenience Classes
// To remove requirement of having to create a QMQTT::Message
// any time we wish to send a message
void QMqttClient::publish(const char *topic, const char *message, QosLevel qos, bool retain)
{
    // is this a memory leak? when to destroy?
    QMQTT::Message msg(_id++,topic,message,qos,retain);
    QMQTT::Client::publish(msg);
}

void QMqttClient::publish(const char *topic, QString message, QosLevel qos, bool retain)
{
    publish(topic, message.toStdString().c_str(), qos, retain);
}

void QMqttClient::publish(QString topic, const char *message, QosLevel qos, bool retain)
{
    publish(topic.toStdString().c_str(), message, qos, retain);
}

void QMqttClient::publish(QString topic, QString message, QosLevel qos, bool retain)
{
    publish(topic.toStdString().c_str(), message.toStdString().c_str(), qos, retain);
}

// convenience method setHost
//
void QMqttClient::setHost(const char *host)
{
    QMQTT::Client::setHost(QHostAddress(host));
}

void QMqttClient::on_disconnected()
{
    // add reconnect logic here if required

    // call stub for reimplementation in derived class
    onMqttDisconnect();
}

void QMqttClient::on_messageReceived(QMQTT::Message)
{
    qDebug() << qPrintable("MqttClient::on_messageReceived(QMQTT::Message)");
}

void QMqttClient::on_connected()
{

    // inform remote users this client is online and available
    // this will be cleared by the last will and testiment
    // message is retained for late joiners
    publish(_onlineMessageTopic, _onlineMessagePayload, QOS_1, _onlineMessageRetain);

    // call stub for reimplementation in derived class
    // TODO: this is not working
    onMqttConnect();

}

void QMqttClient::setName(QString name)
{
    _name = name;
}

// Set payload of message to be sent when
// client comes online
void QMqttClient::setOnlineMessagePayload(const QString message)
{
    _onlineMessagePayload = message;
}

// Set topic of message to be sent when
// client comes online
void QMqttClient::setOnlineMessageTopic(const QString topic)
{
    _onlineMessageTopic= topic;
}

// STUBS
void QMqttClient::onMqttConnect()
{

}

void QMqttClient::onMqttDisconnect()
{

}


