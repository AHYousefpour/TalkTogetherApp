#ifndef MESSAGEDISPLAYER_H
#define MESSAGEDISPLAYER_H

#include <QObject>
#include <QJsonObject>
#include <QTextEdit>

class MessageDisplayer : public QObject
{
    Q_OBJECT
public:
    MessageDisplayer(QTextEdit* displyerMessage);

public slots:
    void displayMessage(QJsonObject json);

signals:
    void updateStatus(QString number);

private:
    QTextEdit* displayerMsg;
};

#endif // MESSAGEDISPLAYER_H
