#ifndef QWST_H
#define QWST_H

#include <QObject>
#include <QWebSocket>

class qwst : public QObject
{
    Q_OBJECT
private:
    QWebSocket socket;
private Q_SLOTS:
    void Connected();
    void Disconnected();
    void Received(const QString& message);
public:
    qwst();
};

#endif // QWST_H
