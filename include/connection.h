#ifndef CONNECT_H
#define CONNECT_H

#include <QThread>
#include <QHostAddress>

class Connection : public QThread
{
    Q_OBJECT

public:
    Connection(QHostAddress address, quint16 port, QString name);

private:
    void run() override;

private slots:
    void handleStatusConnection(bool isConnect);

signals:
    void startUp();
    void changeStateToErrorConnection();

private:
    class Session* session;
};

#endif // CONNECT_H
