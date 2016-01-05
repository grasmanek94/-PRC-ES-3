#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QTcpSocket>
#include <QString>
#include <QTime>

class WebSocketClient
{
    public:
        bool connect(unsigned short port, QString host = "localhost", QString path = "/");
        bool connected();
        void disconnect();
        QString read(size_t minimum_readamount = 0, int timeout = 16);
        QString readUntil(QString needle, int timeout = 16);
        void send(String data);
    private:
        QString getStringTableItem(int index);
        void sendHandshake(QString host = "localhost", QString path = "/");
        QTcpSocket _client;
        bool readHandshake();
        QString readLine();
};

#endif // WEBSOCKETCLIENT_H
