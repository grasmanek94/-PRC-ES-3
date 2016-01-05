#ifndef SYCHRONOUSWEBSOCKETSRESPONDER_H
#define SYCHRONOUSWEBSOCKETSRESPONDER_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QtCore>
#include <QtWebSockets/QWebSocket>

class SychronousWebSocketsResponder : public QThread
{
    Q_OBJECT

private:
    bool connected;
    QWebSocket webSocket;

private Q_SLOTS:
    void Connected();
    void Disconnected();
public:
    SychronousWebSocketsResponder(unsigned short port);

    QString SendDataAndGetReply(const QString& str);
};

#endif // SYCHRONOUSWEBSOCKETSRESPONDER_H
