#include "websocketclient.h"

QString clientHandshake = "GET %1 HTTP/1.1\nUpgrade: WebSocket\nConnection: Upgrade\nHost: %2\nOrigin: RafalMinhTrietWSC\n";
QString serverHandshake = "HTTP/1.1 101";

bool WebSocketClient::connect(unsigned short port, QString host, QString path)
{
    bool result = false;

    if (_client.connectToHost(host, port))
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
    QTime Timer;
    Timer.start();
    while (_client.bytesAvailable() < minimum_readamount && myTimer.elapsed() < timeout)
    { }

    if(_client.bytesAvailable() >= minimum_readamount)
    {
        return QString(_client.read(minimum_readamount));
    }
    return "";
}

QString WebSocketClient::readUntil(QString needle, int timeout)
{
    QTime Timer;
    Timer.start();
    while (_client.bytesAvailable() < minimum_readamount && myTimer.elapsed() < timeout)
    { }

    if(_client.bytesAvailable() >= minimum_readamount)
    {
        return QString(_client.read(minimum_readamount));
    }
    return "";
}

void WebSocketClient::sendHandshake(QString hostname, QString path)
{
    _client.write(clientHandshake.arg(path).arg(hostname));
}

bool WebSocketClient::readHandshake()
{
    bool result = false;
    char character;
    String handshake = "", line;
    int maxAttempts = 300, attempts = 0;

    while(_client.available() == 0 && attempts < maxAttempts)
    {
        delay(100);
        attempts++;
    }

    while((line = readLine()) != "") {
        handshake += line + '\n';
    }

    String response = getStringTableItem(6);
    result = handshake.indexOf(response) != -1;

    if(!result) {
        _client.stop();
    }

    return result;
}

QString WebSocketClient::readLine()
{
    return _client.readLine();
}

void WebSocketClient::send (QString data)
{
    _client.write((char)0);
    _client.write(data);
    _client.write((char)255);
}

