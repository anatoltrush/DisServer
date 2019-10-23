#ifndef HTTPPARSER_H
#define HTTPPARSER_H

#include <QString>
#include <QByteArray>
#include <QVariant>

#include "Constants.h"
#include "../Common/unique.h"
#include "../Common/disDefines.h"
#include "../Primitives/IPrimitives.h"

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
    QString entity, function, bound/*if post*/;

    QString starting_line;
    QStringMap headers;
//}


//{ output data
    QString authorToken; // for authorization
    QVariantMap params; // for GET or DELETE requests
    QList<QString> blocks; // everywhere
    std::unique_ptr<IPrimitives> object; // for POST or PATCH or PUT requests
//}

    void parse(const QByteArray &data);

private:
    void basicParse(const QByteArray &data);

    void getParse();
    void postParse();
    void patchParse();
    void deleteParse();
    void optionParse();
    void optionPut();
    void optionHead();

    QPair<QString, QVariant> parseBlock(const QString &block);
};

//! @} server_part

}

#endif // HTTPPARSER_H
