#include <QTime>
#include <QTcpSocket>
#include <QString>

#include "websocketclient.h"

QString clientHandshake = "GET %1 HTTP/1.1\nUpgrade: WebSocket\nConnection: Upgrade\nHost: %2\nOrigin: RafalMinhTrietWSC\n";
QString serverHandshake = "HTTP/1.1 101";

bool WebSocketClient::connect(unsigned short port, QString host, QString path)
{
    bool result = false;

    _client.connectToHost(host, port);
    if(_client.waitForConnected())
    {
        sendHandshake(host, path);
        result = readHandshake();
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
    return readUntil(-1, timeout);
}

QString WebSocketClient::readUntil(char needle, int timeout)
{
    QTime Timer;
    Timer.start();

    QString buffer = "";
    char c = needle;

    while(
          _client.read(&c, 1) != 1 &&
          c != 0 &&
          Timer.elapsed() < timeout)
    {
        c = needle;
    }

    if(!c)
    {
        while(Timer.elapsed() < timeout && c != needle && c != -1)
            //if needle == -1 @ compile time, compiler will optimize this statement to
            //while(myTimer.elapsed() < timeout && c != -1)
        {
            while(_client.read(&c, 1) == 1 && c != needle && c != -1)
            {
                buffer.append((QChar)c);
            }
        }
    }

    return buffer;
}

void WebSocketClient::sendHandshake(QString hostname, QString path)
{
    _client.write(clientHandshake.arg(path).arg(hostname).toLocal8Bit());
}

bool WebSocketClient::readHandshake(int timeout)
{ 
    bool result = false;
    QString handshake = "";
    QString line;
    QTime Timer;
    Timer.start();

    while(_client.bytesAvailable() == 0 && Timer.elapsed() < timeout)
    {

    }

    while((line = readLine()) != "")
    {
        handshake += line + '\n';
    }

    result = handshake.indexOf(serverHandshake) != -1;

    if(!result)
    {
        _client.disconnectFromHost();
    }

    return result;
}

QString WebSocketClient::readLine(int timeout)
{
    QString line = readUntil('\n', timeout);
    if(line[line.size()-1] == '\r')
    {
        line = line.remove(line.size()-1, 1);
    }
    return line;
}

void WebSocketClient::send(QString data)
{
    static char ZERO = 0;
    static char MINONE = 255;

    _client.write(&ZERO, 1);
    _client.write(data.toLocal8Bit());
    _client.write(&MINONE, 1);
}
