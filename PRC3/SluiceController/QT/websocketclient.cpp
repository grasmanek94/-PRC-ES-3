//Based on https://tools.ietf.org/html/rfc6455
//By Rafal Grasman
//Very basic implementation, does not support ping/pong/binary/etc....
//Just Enough To Get The Job Done (TM)

#include <QTime>
#include <QTcpSocket>
#include <QString>

#include "websocketclient.h"
#include "Base64.h"

const QString clientHandshake = "\
GET / HTTP/1.1\r\n\
Host: %1:%2\r\n\
Upgrade: websocket\r\n\
Connection: Upgrade\r\n\
Sec-WebSocket-Key: %3\r\n\
Sec-WebSocket-Version: 13\r\n\r\n\
";

const QString serverHandshake = "HTTP/1.1 101";

//#define PD(a) std::cout << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ":" << (a) << std::endl

//P.S. It's inefficient as f***...
//But w.e. goal of this excersize is not to implement websockets... so as long as it works we're okay
bool WebSocketClient::connect(unsigned short port, QString host, int timeout)
{
    for(int i = 0; i < 16; ++i)
    {
        security_key[i] = rand() % 256;
    }
    char buffer[64];
    base64_encode(buffer,security_key, 16);
    security_key_str = "";
    security_key_str.append(buffer);

    bool result = false;

    _client.connectToHost(host, port);
    if(_client.waitForConnected())
    {
        this->port = port;
        sendHandshake(host);
        result = readHandshake(timeout);
    }

    return result;
}


bool WebSocketClient::connected()
{
    return _client.ConnectedState == QAbstractSocket::ConnectedState;
}

void WebSocketClient::disconnect()
{
    _client.disconnectFromHost();
}

QString WebSocketClient::readMessage(int timeout)
{
    _client.waitForReadyRead(timeout);
    QString result = _client.readAll();
    //first two bytes are packet type and size
    //reply is never bigger than 125 so we are safe
    result.remove(0, 2);
    //If reply will be bigger anyway ever, just check the second byte for the WS_SIZE16 mask, if true, remove two more bytes
    return result;
}

void WebSocketClient::sendHandshake(QString hostname)
{
    std::string tosend = clientHandshake.arg(hostname).arg(port).arg(security_key_str).toStdString();
    _client.write(tosend.c_str(), tosend.size());
}

bool WebSocketClient::readHandshake(int timeout)
{ 
    bool result = false;
    QString handshake = "";

    _client.waitForReadyRead(timeout);

    handshake = _client.readAll();
    result = handshake.indexOf(serverHandshake) != -1;

    if(!result)
    {
        _client.disconnectFromHost();
    }

    return result;
}


void WebSocketClient::send(QString data)
{
    // First byte
    static const char WS_FIN            = 0x80;
    static const char WS_OPCODE_TEXT    = 0x01;

    // Second byte
    static const char WS_MASK           = 0x80;
    static const char WS_SIZE16         = 126 ;

    QByteArray arr;
    arr.append(WS_OPCODE_TEXT | WS_FIN);
    unsigned short size = data.size();
    if (size > 125)
    {
        arr.append(WS_SIZE16 | WS_MASK);
        arr.append((uint8_t) (size >> 8));
        arr.append((uint8_t) (size & 0xFF));
    }
    else
    {
        arr.append((uint8_t) size | WS_MASK);
    }

    unsigned char mask[4] =
    {
        (unsigned char)(rand() % 256),
        (unsigned char)(rand() % 256),
        (unsigned char)(rand() % 256),
        (unsigned char)(rand() % 256)
    };

    arr.append(mask[0]);
    arr.append(mask[1]);
    arr.append(mask[2]);
    arr.append(mask[3]);

    std::string str = data.toStdString();

    for (unsigned short i = 0; i < size; ++i)
    {
        arr.append(str[i] ^ mask[i % 4]);
    }

    _client.write(arr);
    _client.flush();
}
