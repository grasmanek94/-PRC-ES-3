#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QTcpSocket>
#include <QString>

class WebSocketClient
{
    public:
        bool connect(unsigned short port, QString host = "localhost", QString path = "/");
        bool connected();
        void disconnect();
        QString readMessage(int timeout = 16);
        void send(QString data);
    private:
        QString readUntil(char needle = -1, int timeout = 16);
        QString readLine(int timeout = 16);
        void sendHandshake(QString hostname = "localhost", QString path = "/");
        bool readHandshake(int timeout = 16);

        QTcpSocket _client;
};

#endif // WEBSOCKETCLIENT_H
