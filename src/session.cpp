#include "session.h"
#include <QJsonDocument>
#include <QEventLoop>
#include "messageType.h"

Session::Session(QHostAddress address, quint16 port, QString name)
    : address(address), port(port), name(name)
{
    QObject::connect(&clientSocket, &QTcpSocket::readyRead, this, &Session::recvMessage);

    connectToServer();
}

void Session::connectToServer()
{
    clientSocket.connectToHost(address, port, QTcpSocket::ReadWrite);

    if(clientSocket.isValid())
        qDebug() << "socket is valid";
    if(clientSocket.isOpen())
        qDebug() << "socket is open";
    if(clientSocket.isWritable())
        qDebug() << "socket is writeable";


    QJsonObject json;
    json.insert("type", NewConnection);
    json.insert("time", QTime::currentTime().toString());
    json.insert("name", name);

    sendMessage(json);
}

void Session::disconnect()
{
    QJsonObject json;
    json.insert("type", MessageType::Disconnect);

    sendMessage(json);

    clientSocket.close();
}

void Session::sendMessage(QJsonObject json)
{
    QJsonDocument jdoc(json);
    QByteArray buffer = jdoc.toJson();

    int size = buffer.length();
    std::string len = std::to_string(size);

    clientSocket.write(len.c_str(), sizeof(char*));	
    clientSocket.write(buffer);
}

void Session::recvMessage()
{
    QByteArray buffer = clientSocket.readAll();
    clientSocket.flush();

    QJsonDocument jdoc = QJsonDocument::fromJson(buffer);

    QJsonObject json = jdoc.object();

    emit message(json);
}

