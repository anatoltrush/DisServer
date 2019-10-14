#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#define IS_HTML

#include "Constants.h"
#include "../Primitives/IPrimitives.h"

namespace dis{

//! @addtogroup server_part
//! @{

class HttpResponse
{
public:
    HttpResponse();

    QByteArray responseQBA;

    void createResponse(int code);

    void admitResult(const QList<QString> &uuids);
    void admitResult(const std::vector<std::unique_ptr<IPrimitives> > &&ents);

private:
    static QString serverName;
    static QString httpVersion;
    static QString nextLn;

    QList<QString> uuids;
    std::vector<std::unique_ptr<IPrimitives>> entities;

//    QString starting_line;
//    using QStringMap = QMap<QString, QString>;
//    typedef QMap<QString, QString> QStringMap;
//    QStringMap headers;
//    QList<QString> headers;
//    QVariantMap message_body;

    // 1 step
    void createStartLine(int status);
    // 2 step
    void createHeaders();
    // 3 step
    void createMessage();

    QString bound = "separator";
};

//! @} server_part

}

#endif // HTTPRESPONSE_H
