#include "qwst.h"

#include <iostream>

qwst::qwst()
{
    socket.connect(&socket, &QWebSocket::connected, this, &qwst::Connected);
    socket.connect(&socket, &QWebSocket::textMessageReceived, this, &qwst::Received);
    socket.open(QUrl("ws://192.168.137.128:5555"));
}

void qwst::Connected()
{
    std::cout << "connected" << std::endl;
    socket.sendTextMessage("SetDoorLeft:close");
}

void qwst::Disconnected()
{
    std::cout << "disconnected" << std::endl;
}

void qwst::Received(const QString& message)
{
    std::cout << "Received " << message.toStdString() << std::endl;
}
