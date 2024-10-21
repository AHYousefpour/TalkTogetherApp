#ifndef LOGIN_H
#define LOGIN_H

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
    void ChangeStateToErrorConnection();

private:
    Ui::Login *ui;
    class Connection* connection;
    void changeStateToConnecting(const bool visible);
    void showError(const bool show);
    void setRegexToInputs();
};

#endif // LOGIN_H
