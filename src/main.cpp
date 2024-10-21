#include "login.h"
#include <QApplication>
#include <QTextStream>
#include <QList>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login login;
    login.show();

    return a.exec();
}
