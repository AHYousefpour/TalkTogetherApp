#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QObject>
#include <QJsonObject>
#include <QApplication>

class Session : public QObject
{
    Q_OBJECT

public:
    Session(Session&) = delete;
    Session() = delete;
    static Session* getInctanse(QString address, quint16 port, QString name);
    static Session *getInctanse();
    void connectToServer();
    void sendMessage(QJsonObject msg);

    QString address() { return m_address; }
    quint16 port() { return m_port; }

private:
    Session(QString address, quint16 port, QString name);
    ~Session();

public slots:
    void disconnect();

private slots:
    void sendInfo();
    void recvMessage();
    void handleState(QAbstractSocket::SocketState state);
    void handleError(QAbstractSocket::SocketError error);

signals:
    void message(QJsonObject json);
    void changedStatus(bool isConnect);
    void connecting(bool);
    void connected();
    void errorOccurred(QString error);

private:
    static Session* session;
    QTcpSocket* clientSocket;
    QString m_address;
    quint16 m_port;
    QString m_name;
};

#endif // CLIENT_H
