#include "sychronouswebsocketsresponder.h"

void SychronousWebSocketsResponder::onTextMessageReceived(QString message)
{
    str = message;
}

SychronousWebSocketsResponder::SychronousWebSocketsResponder(unsigned short port)
{
    connect(&webSocket, &QWebSocket::textMessageReceived,
            this, &SychronousWebSocketsResponder::onTextMessageReceived);
    webSocket.open(QUrl(QString("ws://localhost:") + port));
}

qint64 SychronousWebSocketsResponder::SendData(const QString& str)
{
    return webSocket.sendTextMessage(str);
}

QString SychronousWebSocketsResponder::GetData(int timeout)
{
    QString ret;
    QTime myTimer;
    myTimer.start();
    while(!str.length() && myTimer.elapsed() <= timeout)
    {
        QCoreApplication::processEvents();
    }
    ret = str;
    str = "";
    return ret;
}
