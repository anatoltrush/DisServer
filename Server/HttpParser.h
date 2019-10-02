#ifndef HTTPPARSER_H
#define HTTPPARSER_H

#include <QString>
#include <QByteArray>
#include <QMap>

// TODO: define errors and statuses

namespace dis{
class HttpParser
{
public:
    HttpParser();

    QString starting_line;

    using QStringMap = QMap<QString, QString>;
//    typedef QMap<QString, QString> QStringMap;
    QStringMap headers;

    QString message_body;

    void parse(const QByteArray &data);

};
}

#endif // HTTPPARSER_H

// using Delta = vector<Offset>;
