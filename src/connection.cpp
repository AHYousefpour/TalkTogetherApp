#include "connection.h"
#include "session.h"
#include <QObject>

Connection::Connection(QHostAddress address, quint16 port, QString name)
{
    session = Session::getInctanse(address, port, name);

    QObject::connect(session, &Session::changedStatus, this, &Connection::handleStatusConnection);
}

void Connection::run()
{
    session->connectToServer();
}

void Connection::handleStatusConnection(bool isConnect)
{
    if(isConnect)
        emit startUp();
    else
        emit changeStateToErrorConnection();
}
