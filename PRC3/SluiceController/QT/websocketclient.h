#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QTcpSocket>
#include <QString>

class WebSocketClient
{
    public:
        bool connect(unsigned short port, QString host = "192.168.137.128", int timeout = 3000);
        bool connected();
        void disconnect();
        QString readMessage(int timeout = 16);
        void send(QString data);
    private:
        void sendHandshake(QString hostname);
        bool readHandshake(int timeout = 9999);

        unsigned short port;
        char security_key[16];
        QString security_key_str;
        QTcpSocket _client;
};

#endif // WEBSOCKETCLIENT_H
