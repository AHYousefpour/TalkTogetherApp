#ifndef TALKTOGETHER_H
#define TALKTOGETHER_H

#include <QHostAddress>
#include <QMainWindow>
#include "session.h"
#include "messageDisplayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TalkTogether; }
QT_END_NAMESPACE

class TalkTogether : public QMainWindow
{
    Q_OBJECT

public:
    static TalkTogether* getInctanse(QString name);

private slots:
    void on_sendMsgBtn_clicked();
    void updateStatus(QString number);
    void on_disconnectBtn_clicked();

signals:
    void recvMessage();

private:
    TalkTogether(QString name, QWidget *parent = nullptr);
    ~TalkTogether();
    bool verifyMsg(QString msg);
    bool isJustSpace(QString msg);

    Ui::TalkTogether *ui;
    static TalkTogether* talkTogether;
    static Session* session;
    MessageDisplayer* messageDisplayer;
    QString name;
};
#endif // TALKTOGETHER_H
