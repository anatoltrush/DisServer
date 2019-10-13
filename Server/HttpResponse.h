#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include "Constants.h"
#include "HttpParser.h"
#include "../Primitives/IPrimitives.h"

// TODO: MESSAGE???

namespace dis{

//! @addtogroup server_part
//! @{

class HttpResponse
{
public:
    HttpResponse();

    void createResponse(const HttpParser &parser, int code);

    void admitResult(const QList<QString> &uuid);
    void admitResult(const std::vector<std::unique_ptr<IPrimitives> > &&ents);

    const QByteArray &toQByteArray();

private:
    static QString serverName;
    static QString httpVersion;

    QList<QString> uuid;
    std::vector<std::unique_ptr<IPrimitives>> entities;

    QString starting_line;
    using QStringMap = QMap<QString, QString>;
//    typedef QMap<QString, QString> QStringMap;
    QStringMap headers;
    QString message_body;

    QString responseQSTR;
    QByteArray responseQBA;

    // 1 step
    void createStartLine(int status);
    // 2 step
    void createHeaders(const HttpParser &parser);
    // 3 step
    void createMessage();

    void collectRespQstr();
};

//! @} server_part

}

#endif // HTTPRESPONSE_H
