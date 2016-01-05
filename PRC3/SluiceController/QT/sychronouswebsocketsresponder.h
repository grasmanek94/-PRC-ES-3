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
    QString str;

private Q_SLOTS:
    void onTextMessageReceived(QString message);
    void Connected();
    void Disconnected();
public:
    SychronousWebSocketsResponder(unsigned short port);

    qint64 SendData(const QString& str);
    QString GetData(int timeout = 16);
};

#endif // SYCHRONOUSWEBSOCKETSRESPONDER_H
