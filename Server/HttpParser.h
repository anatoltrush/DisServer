#ifndef HTTPPARSER_H
#define HTTPPARSER_H

#include <QString>
#include <QByteArray>
#include <QMap>
#include <QVariant>

#include "Constants.h"
#include "../Common/unique.h"
#include "../Primitives/IPrimitives.h"

// TODO: QString to QBA!!! important

namespace dis{

//! @addtogroup server_part
//! @{

class HttpParser
{
public:
    HttpParser();

    int status = HTTP_BAD_REQUEST;

//{ input raw data
    QString method, address, httpVers;
    QString entity, function, bound;

    QString starting_line;
    using QStringMap = QMap<QString, QString>;
//    typedef QMap<QString, QString> QStringMap;
    QStringMap headers;
    QByteArray message_body;
//}


//{ output data
    QString authorToken; // for authorization
    QList<QVariantMap> params; // for GET or DELETE requests
    std::unique_ptr<IPrimitives> object; // for POST or PATCH requests
//}

    void parse(const QByteArray &data);

    // parse if GET
    // parse if POST
    // parse if PATCH
    // parse if DELETE

private:
};

//! @} server_part

}

#endif // HTTPPARSER_H
