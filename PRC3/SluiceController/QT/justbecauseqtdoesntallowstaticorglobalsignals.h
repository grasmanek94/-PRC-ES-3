#ifndef JUSTBECAUSEQTDOESNTALLOWSTATICORGLOBALSIGNALS_H
#define JUSTBECAUSEQTDOESNTALLOWSTATICORGLOBALSIGNALS_H

#include <QString>
#include <QtCore>
#include <QtWebSockets/QWebSocket>
#include <QObject>
#include <iostream>

class JustBecauseQtDoesntAllowStaticOrGlobalSignals : public QObject
{
private:
    Q_OBJECT
    QString result;
private Q_SLOTS:
    void UpdateResult(QString message);
public:
    JustBecauseQtDoesntAllowStaticOrGlobalSignals();
    QString run(QWebSocket* socket, const QString& str);
    ~JustBecauseQtDoesntAllowStaticOrGlobalSignals();
};

#endif // JUSTBECAUSEQTDOESNTALLOWSTATICORGLOBALSIGNALS_H
