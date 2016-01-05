#ifndef JUSTBECAUSEQTDOESNTALLOWSTATICORGLOBALSIGNALS_H
#define JUSTBECAUSEQTDOESNTALLOWSTATICORGLOBALSIGNALS_H

#include <QString>
#include <QtCore>
#include <QtWebSockets/QWebSocket>
#include <QObject>
#include <QThread>
#include <iostream>

class JustBecauseQtDoesntAllowStaticOrGlobalSignals : public QObject
{
private:
    Q_OBJECT
    bool got;
    QString result;
private Q_SLOTS:
    void Connected();
    void UpdateResult(QString message);
public:
    JustBecauseQtDoesntAllowStaticOrGlobalSignals();
    QString run(QWebSocket* socket, const QString& str);
    ~JustBecauseQtDoesntAllowStaticOrGlobalSignals();
};

#endif // JUSTBECAUSEQTDOESNTALLOWSTATICORGLOBALSIGNALS_H
