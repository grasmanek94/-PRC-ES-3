#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

class WebSocketClient
{
    public:
        bool connect(unsigned short port, string host = "localhost", int timeout = 3000);
        bool connected();
        void disconnect();
        string readMessage(int timeout = 16);
        void send(QString data);
    private:
        void sendHandshake(string hostname);
        bool readHandshake(int timeout = 9999);

        unsigned short port;
        char security_key[16];
        string security_key_str;
};

#endif // WEBSOCKETCLIENT_H
