#include "justbecauseqtdoesntallowstaticorglobalsignals.h"

void JustBecauseQtDoesntAllowStaticOrGlobalSignals::UpdateResult(QString message)
{
    std::cout << "RECEIVED: " << message.toStdString() << std::endl;
    result = message;
}

JustBecauseQtDoesntAllowStaticOrGlobalSignals::JustBecauseQtDoesntAllowStaticOrGlobalSignals()
{}

QString JustBecauseQtDoesntAllowStaticOrGlobalSignals::run(QWebSocket* socket, const QString& str)
{
    QEventLoop loop;

    loop.connect(socket, &QWebSocket::textMessageReceived, this, &JustBecauseQtDoesntAllowStaticOrGlobalSignals::UpdateResult);

    std::cout << "SENDING: " << str.toStdString() << " to " << socket->requestUrl().toString().toStdString() << " RES: " <<
                 socket->sendTextMessage(str) << std::endl;

    loop.exec();

    std::cout << "RESULT: " << result.toStdString() << std::endl;
    return result;
}

JustBecauseQtDoesntAllowStaticOrGlobalSignals::~JustBecauseQtDoesntAllowStaticOrGlobalSignals()
{}
