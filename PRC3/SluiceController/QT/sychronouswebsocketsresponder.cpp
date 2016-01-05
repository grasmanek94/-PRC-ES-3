#include <QMessageBox>
#include "sychronouswebsocketsresponder.h"

void SychronousWebSocketsResponder::onTextMessageReceived(QString message)
{
    QMessageBox msgBox;
    msgBox.setText("RECEIVED");
    msgBox.setInformativeText(message);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    str = message;
}

SychronousWebSocketsResponder::SychronousWebSocketsResponder(unsigned short port)
    : connected(false)
{
    connect(&webSocket, &QWebSocket::textMessageReceived,
            this, &SychronousWebSocketsResponder::onTextMessageReceived);
    connect(&webSocket, &QWebSocket::connected, this, &SychronousWebSocketsResponder::Connected);
    connect(&webSocket, &QWebSocket::disconnected, this, &SychronousWebSocketsResponder::Disconnected);
    webSocket.open(QUrl(QString("ws://localhost:%1").arg(port)));
    QMessageBox msgBox;
    msgBox.setText("OPENING");
    msgBox.setInformativeText(QString("ws://localhost:%1").arg(port));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    QTime myTimer;
    myTimer.start();
    while(!connected && myTimer.elapsed() <= 3000)
    {
        QCoreApplication::processEvents();
    }
\
    msgBox.setText("AFTER");
    msgBox.setInformativeText(connected ? "YES" : "NO");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void SychronousWebSocketsResponder::Connected()
{
    QMessageBox msgBox;
    msgBox.setText("CONNECTED");
    msgBox.setInformativeText("OK");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    connected = true;
}

void SychronousWebSocketsResponder::Disconnected()
{
    QMessageBox msgBox;
    msgBox.setText("CONNECTED");
    msgBox.setInformativeText("FAIL");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    connected = false;
    webSocket.open(webSocket.requestUrl());
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
