#include "login.h"
#include "ui_login.h"
#include "talkTogether.h"
#include "connection.h"
#include <QObject>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QPixmap>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    changeStateToConnecting(false);
    showError(false);
    setRegexToInputs();

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

void Login::changeStateToConnecting(const bool value)
{
    ui->backgroundWidget->setVisible(!value);
    ui->inputIPAddress->setVisible(!value);
    ui->inputName->setVisible(!value);
    ui->inputPort->setVisible(!value);
    ui->connectBtn->setVisible(!value);
    ui->loadingWidget->setVisible(value);
    ui->connectingLable->setVisible(value);
    ui->label->setStyleSheet(value ? "color: black" : "color: white");
    this->repaint();
}

void Login::showError(const bool show)
{
    ui->errorIcon->setVisible(show);
    ui->errorText->setVisible(show);
}

void Login::setRegexToInputs()
{
    QRegularExpression regex("^((25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])$");
    QRegularExpressionValidator* regexValidatorOfIP = new QRegularExpressionValidator(regex);
    ui->inputIPAddress->setValidator(regexValidatorOfIP);

    regex.setPattern("^[A-Za-z]{3,25}$");
    QRegularExpressionValidator* regexValidatorOfName = new QRegularExpressionValidator(regex);
    ui->inputName->setValidator(regexValidatorOfName);

    regex.setPattern("^(?:[1-9][0-9]{0,3}|[1-5][0-9]{4}|65536)$");
    QRegularExpressionValidator* regexValidatorOfPort = new QRegularExpressionValidator(regex);
    ui->inputPort->setValidator(regexValidatorOfPort);
}

void Login::connectToServer()
{
    ui->connectingLable->setText(QString("Connecting to %1").arg(ui->inputIPAddress->text()));
    changeStateToConnecting(true);
    showError(false);

    QHostAddress address(ui->inputIPAddress->text());
    quint16 port = ui->inputPort->text().toUInt();

    connection = new Connection(address, port, ui->inputName->text());

    QObject::connect(connection, &Connection::startUp, this, &Login::startUpApp);
    QObject::connect(connection, &Connection::changeStateToErrorConnection, this, &Login::ChangeStateToErrorConnection);

    connection->start();
}

void Login::ChangeStateToErrorConnection()
{
    changeStateToConnecting(false);
    showError(true);
}

