#ifndef HTTPPARSER_H
#define HTTPPARSER_H

#include <QString>
#include <QByteArray>
#include <QMap>
#include <QVariant>

#include "Constants.h"

namespace dis{

//! @addtogroup server_part
//! @{

class HttpParser
{
public:
    HttpParser();

    int status = HTTP_BAD_REQUEST;

    QString method, address, httpVers;
    QString entity, function;

    QString starting_line;

    using QStringMap = QMap<QString, QString>;
//    typedef QMap<QString, QString> QStringMap;
    QStringMap headers;

    QString message_body;

    QList<QVariant> params;

    void parse(const QByteArray &data);

};

//! @} server_part

}

#endif // HTTPPARSER_H
