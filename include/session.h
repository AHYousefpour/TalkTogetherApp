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
    static Session* getInctanse(QHostAddress address, quint16 port, QString name);
    void connectToServer();
    void sendMessage(QJsonObject msg);

private:
    Session(QHostAddress address, quint16 port, QString name);
    ~Session();

public slots:
    void disconnect();

private slots:
    void recvMessage();
    void connect();

signals:
    void message(QJsonObject json);
    void changedStatus(bool isConnect);

private:
    static Session* session;
    QHostAddress address;
    quint16 port;
    QString name;
    QTcpSocket clientSocket;
    bool isConnect = false;
};

#endif // CLIENT_H
