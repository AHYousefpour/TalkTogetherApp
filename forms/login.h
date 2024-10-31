#ifndef LOGIN_H
#define LOGIN_H

#include "ui_login.h"
#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void startUpApp();
    void connectToServer();
    void ChangeStateToErrorConnection(QString error);

private:
    Ui::Login *ui;
    class Connection* connection;
    void showError(const bool show);
    void setRegexToInputs();
    void changeStateToConnecting(const bool value);
};

#endif // LOGIN_H
