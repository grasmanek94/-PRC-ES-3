#include <QMessageBox>
#include <QFuture>
#include <QtConcurrent/QtConcurrentRun>
#include "sychronouswebsocketsresponder.h"
#include "justbecauseqtdoesntallowstaticorglobalsignals.h"
#include <iostream>

QString threadedSendAndWaitForReply(QWebSocket* socket, const QString& str)
{
    JustBecauseQtDoesntAllowStaticOrGlobalSignals justbecauseIcan;
    return justbecauseIcan.run(socket, str);
}

SychronousWebSocketsResponder::SychronousWebSocketsResponder(unsigned short port)
    : connected(false)
{
    connect(&webSocket, &QWebSocket::connected, this, &SychronousWebSocketsResponder::Connected);
    connect(&webSocket, &QWebSocket::disconnected, this, &SychronousWebSocketsResponder::Disconnected);
    webSocket.open(QUrl(QString("ws://localhost:%1").arg(port)));
    QTime myTimer;
    myTimer.start();
    while(!connected && myTimer.elapsed() <= 3000)
    {
        QCoreApplication::processEvents();
    }
}

void SychronousWebSocketsResponder::Connected()
{
    connected = true;
}

void SychronousWebSocketsResponder::Disconnected()
{
    connected = false;
    webSocket.open(webSocket.requestUrl());
}

QString SychronousWebSocketsResponder::SendDataAndGetReply(const QString& str)
{
    std::cout << (connected ? "YES" : "NO") << std::endl;
    QFuture<QString> future = QtConcurrent::run(threadedSendAndWaitForReply, &webSocket, str);
    return future.result();
}
