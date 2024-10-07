#include "messageDisplayer.h"
#include "messageType.h"

MessageDisplayer::MessageDisplayer(QTextEdit *displyerMessage)
    :displayerMsg(displyerMessage)
{

}

void MessageDisplayer::displayMessage(QJsonObject json)
{
    int type = json.value("type").toInt();

    switch (type) {
    case NewConnection: {
        displayerMsg->append(
            "(" + json.value("time").toString() + ") " +
            json.value("name").toString() +
            "<p style=color:green;> has joined to server.</p>"
        );
    }break;

    case Status: {
        emit updateStatus(json.value("number").toString());
    }break;

    case Message: {
        displayerMsg->append(
            "(" + json.value("time").toString() + ") " +
            json.value("name").toString() + ": " +
            json.value("message").toString()
        );
    }break;

    case Disconnect: {
        displayerMsg->append(
            "(" + json.value("time").toString() + ") " +
            json.value("name").toString() +
            "<p style=color:red;> has disconnected from server.</p>"
        );
    }break;

    case WelcomeMessage:
        displayerMsg->append(
           "<p style=color:green;>" + json.value("message").toString() + "</p>"
        );
        break;
    }
}
