#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include "HttpParser.h"
#include "../Primitives/IPrimitives.h"

// TODO: define errors and statuses

namespace dis{

//! @addtogroup server_part
//! @{

class HttpResponse
{
public:
    HttpResponse();

    void createResponse(const HttpParser &parser);

    void admitResult(const QList<QString> &uuid);
    void admitResult(const QList<IPrimitives> &entities);

    const QByteArray &toQByteArray();

private:
    QString starting_line;
    using QStringMap = QMap<QString, QString>;
//    typedef QMap<QString, QString> QStringMap;
    QStringMap headers;
    QString message_body;

    QString responseQSTR;
    QByteArray responseQBA;

    void createStartLine(int status, const QString &reasonPhrase, const QString ver = "HTTP/1.1");
    void createHeaders();
    void createMessage();

    void collectRespQstr();
};

//! @} server_part

}

#endif // HTTPRESPONSE_H
