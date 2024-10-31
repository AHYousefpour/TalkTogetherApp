#include "session.h"
#include <QJsonDocument>
#include "messageType.h"

Session* Session::session = nullptr;

Session::Session(QString address, quint16 port, QString name)
    : m_address(address), m_port(port), m_name(name)
{
    clientSocket = new QTcpSocket(this);

    QObject::connect(clientSocket, &QTcpSocket::connected, this, &Session::sendInfo);
    QObject::connect(clientSocket, &QTcpSocket::readyRead, this, &Session::recvMessage);
    QObject::connect(clientSocket, &QTcpSocket::stateChanged, this, &Session::handleState);
    QObject::connect(clientSocket, &QTcpSocket::errorOccurred, this, &Session::handleError);
}

Session::~Session()
{
    delete clientSocket;
    delete session;
}

Session *Session::getInctanse(QString address, quint16 port, QString name)
{
    if(session == nullptr)
    {
        session = new Session(address, port, name);
    }

    return session;
}

Session *Session::getInctanse()
{
    return session;
}

void Session::connectToServer()
{
    clientSocket->connectToHost(session->address(), session->port());
}

void Session::sendInfo()
{
    QJsonObject json;
    json.insert("type", NewConnection);
    json.insert("time", QTime::currentTime().toString());
    json.insert("name", m_name);

    sendMessage(json);
}

void Session::disconnect()
{
    QJsonObject json;
    json.insert("type", MessageType::Disconnect);
    json.insert("time", QTime::currentTime().toString());
    json.insert("name", m_name);

    sendMessage(json);

    clientSocket->close();
    this->~Session();
}

void Session::sendMessage(QJsonObject json)
{
    QJsonDocument jdoc(json);
    QByteArray buffer = jdoc.toJson();

    int size = buffer.length();
    std::string len = std::to_string(size);

    clientSocket->write(len.c_str(), sizeof(char*));
    clientSocket->write(buffer);
}

void Session::recvMessage()
{
    QByteArray buffer = clientSocket->readAll();

    QJsonDocument jdoc = QJsonDocument::fromJson(buffer);

    QJsonObject json = jdoc.object();

    emit message(json);
}

void Session::handleState(QAbstractSocket::SocketState state)
{
    switch (state) {
    case QAbstractSocket::ConnectingState: emit connecting(true); break;
    case QAbstractSocket::ConnectedState: emit connected(); break;
    default:
        break;
    }
}

void Session::handleError(QAbstractSocket::SocketError error)
{
    switch(error)
    {
    case QAbstractSocket::ConnectionRefusedError: emit errorOccurred("The connection was refused by the peer (or timed out)."); break;
    case QAbstractSocket::HostNotFoundError: emit errorOccurred("The host address was not found."); break;
    case QAbstractSocket::NetworkError: emit errorOccurred("An error occurred with the network."); break;
    default: emit errorOccurred("UnKnown Error.");
        break;
    }
}


