#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QObject>
#include <QJsonObject>

class Session : public QObject
{
    Q_OBJECT
public:
    Session(Session&) = delete;
    Session(QHostAddress address, quint16 port, QString name);
    void connectToServer();
    void sendMessage(QJsonObject msg);

public slots:
    void disconnect();

private slots:
    void recvMessage();

signals:
    void message(QJsonObject json);

private:
    QHostAddress address;
    quint16 port;
    QString name;
    QTcpSocket clientSocket;
};

#endif // CLIENT_H
