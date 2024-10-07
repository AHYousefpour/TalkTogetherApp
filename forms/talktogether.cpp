#include "talkTogether.h"
#include "./ui_talkTogether.h"
#include <QString>
#include <QObject>
#include <QPushButton>
#include <QJsonObject>
#include <QTime>
#include "messageType.h"

TalkTogether* TalkTogether::talkTogether = nullptr;
Session* TalkTogether::session = nullptr;

TalkTogether::TalkTogether(QString name, QWidget *parent)
    : QMainWindow(parent), name(name)
    , ui(new Ui::TalkTogether)
{
    ui->setupUi(this);

    messageDisplayer = new MessageDisplayer(ui->msgDisplayer);

    QObject::connect(messageDisplayer, &MessageDisplayer::updateStatus, this, &TalkTogether::updateStatus);
    QObject::connect(session, &Session::message, messageDisplayer, &MessageDisplayer::displayMessage);

    this->show();
}

TalkTogether::~TalkTogether()
{
    delete session;
    delete messageDisplayer;
    delete talkTogether;
}

TalkTogether* TalkTogether::getInctanse(QHostAddress address, quint16 port, QString name)
{
    if(talkTogether == nullptr)
    {
        session = new Session(address, port, name);
        talkTogether = new TalkTogether(name);
    }

    return talkTogether;
}


void TalkTogether::on_sendMsgBtn_clicked()
{
    QString msg = ui->inputMsg->text();
    if(verifyMsg(msg))
    {
        QJsonObject json;
        json.insert("type", MessageType::Message);
        json.insert("name", name);
        json.insert("time", QTime::currentTime().toString());
        json.insert("message", msg);


        ui->msgDisplayer->append(msg);
        session->sendMessage(json);
    }
    ui->inputMsg->clear();
}

void TalkTogether::updateStatus(QString number)
{
    ui->statusL->setText("Online: " + number);
}

bool TalkTogether::verifyMsg(QString msg)
{
    if(msg.isNull() || msg.isEmpty())
        return false;
    if(isJustSpace(msg))
        return false;

    return true;
}

bool TalkTogether::isJustSpace(QString msg)
{
    int count = 0;
    for(int index = 0; index < msg.length(); index++)
    {
        if(msg[index] == ' ')
            count++;
    }

    if(count == msg.length())
        return true;

    return false;
}


void TalkTogether::on_disconnectBtn_clicked()
{
    session->disconnect();
}

