#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include "Constants.h"
#include "HttpParser.h"
#include "../Primitives/IPrimitives.h"

namespace dis{

//! @addtogroup server_part
//! @{

class HttpResponse
{
public:
    HttpResponse();

    QByteArray responseQBA;

    QString authToken;

    void createResponse(const HttpParser &parser, int code);

    void admitResult(const QList<QString> &uuids);
    void admitResult(std::vector<std::unique_ptr<IPrimitives> > &ents);

private:
    static QString serverName;
    static QString httpVersion;
    static QString nextLn;

    QList<QString> strings;
    std::vector<std::unique_ptr<IPrimitives> > entities;

    // 1 step
    void createStartLine(int status);
    // 2 step
    void createHeaders();
    // 3 step
    void createMessage(const HttpParser &parser);

    QString bound = "separator";
};

//! @} server_part

}

#endif // HTTPRESPONSE_H
