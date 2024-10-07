#include "login.h"
#include "ui_login.h"
#include "talkTogether.h"
#include <QObject>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    ui->quickWidget->setParent(this);

    QObject::connect(ui->connectBtn, &QPushButton::clicked, this, &Login::startUpApp);
    QObject::connect(ui->connectBtn, &QPushButton::clicked, this, &Login::connectToServer);
}

Login::~Login()
{
    delete ui;
}

void Login::startUpApp()
{
    QHostAddress address(ui->inputIPAddress->text());
    quint16 port = ui->inputPort->text().toUInt();
    TalkTogether* talkTogether = TalkTogether::getInctanse(address, port, ui->inputName->text());

    this->~Login();
}

void Login::connectToServer()
{    
    qDebug() << "connect";
}

