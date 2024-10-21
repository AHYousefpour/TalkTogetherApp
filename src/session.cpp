#include "session.h"
#include <QJsonDocument>
#include <QEventLoop>
#include "messageType.h"
#include <QThread>

Session* Session::session = nullptr;
void prepareDataForSending(QByteArray& buffer);

Session::Session(QHostAddress address, quint16 port, QString name)
    : address(address), port(port), name(name)
{
    QObject::connect(&clientSocket, &QTcpSocket::connected, this, &Session::connect);
    QObject::connect(&clientSocket, &QTcpSocket::readyRead, this, &Session::recvMessage);
}

Session::~Session()
{
    delete session;
}

Session *Session::getInctanse(QHostAddress address, quint16 port, QString name)
{
    if(session == nullptr)
    {
        session = new Session(address, port, name);
    }

    return session;
}

void Session::connectToServer()
{
    QThread::currentThread()->msleep(3000);
    clientSocket.connectToHost(address, port, QTcpSocket::ReadWrite);

    QJsonObject json;
    json.insert("type", NewConnection);
    json.insert("time", QTime::currentTime().toString());
    json.insert("name", name);

    sendMessage(json);

    emit changedStatus(isConnect);
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

    //prepareDataForSending(buffer);

    int size = buffer.length();
    std::string len = std::to_string(size);

    clientSocket.write(len.c_str(), sizeof(char*));
    clientSocket.write(buffer);
}

void prepareDataForSending(QByteArray& buffer)
{
    QList<QString> list;
    QTextStream text(buffer);
    QString line;

    while(text.readLineInto(&line))
    {
        list.append(line);
    }

    buffer.clear();
    QList<QString>::reverse_iterator iter = list.rbegin();
    while(iter != list.rend())
    {
        QString temp = *iter;
        buffer.append(temp.toStdString().c_str());
        iter++;
    }
}

void Session::recvMessage()
{
    QByteArray buffer = clientSocket.readAll();

    QJsonDocument jdoc = QJsonDocument::fromJson(buffer);

    QJsonObject json = jdoc.object();

    emit message(json);
}

void Session::connect()
{
    isConnect = true;
}

