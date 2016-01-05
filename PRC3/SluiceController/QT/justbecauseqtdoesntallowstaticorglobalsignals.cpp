#include "justbecauseqtdoesntallowstaticorglobalsignals.h"

void JustBecauseQtDoesntAllowStaticOrGlobalSignals::UpdateResult(QString message)
{
    std::cout << "RECEIVED: " << message.toStdString() << std::endl;
    result = message;
    got = true;
}

void JustBecauseQtDoesntAllowStaticOrGlobalSignals::Connected()
{
    got = true;
}

JustBecauseQtDoesntAllowStaticOrGlobalSignals::JustBecauseQtDoesntAllowStaticOrGlobalSignals()
    : QObject()
{}

QString JustBecauseQtDoesntAllowStaticOrGlobalSignals::run(QWebSocket* socket, const QString& str)
{
    QWebSocket webSocket;

    connect(&webSocket, &QWebSocket::connected, this, &JustBecauseQtDoesntAllowStaticOrGlobalSignals::Connected);
    connect(&webSocket,&QWebSocket::textMessageReceived, this, &JustBecauseQtDoesntAllowStaticOrGlobalSignals::UpdateResult);
    //QEventLoop loop;

    webSocket.open(socket->requestUrl());

    std::cout << "CONNECTING TO: " << webSocket.requestUrl().toString().toStdString() << std::endl;
    got = false;
    while(!got)
    {
        QCoreApplication::processEvents();
    }

    //loop.connect(socket, &QWebSocket::textMessageReceived, this, &JustBecauseQtDoesntAllowStaticOrGlobalSignals::UpdateResult);

    std::cout << "SENDING: " << str.toStdString() << " to " << webSocket.requestUrl().toString().toStdString() << " RES: " <<
                 webSocket.sendTextMessage(str) << std::endl;
    got = false;
    while(!got)
    {
        QCoreApplication::processEvents();
    }
    //loop.exec();

    std::cout << "RESULT: " << result.toStdString() << std::endl;
    return result;
}

JustBecauseQtDoesntAllowStaticOrGlobalSignals::~JustBecauseQtDoesntAllowStaticOrGlobalSignals()
{}
