#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include "../Common/Constants.h"
#include "HttpParser.h"
#include "../Primitives/IPrimitive.h"

namespace dis{

//! @addtogroup server_part
//! @{
//! This class send only ONE entity! (can to send more but need to correct)
class HttpResponse
{
public:
    HttpResponse() = default;
    ~HttpResponse() = default;

    QByteArray responseQBA;

    QString authToken;

    void createResponse(const HttpParser &parser, int code);

    void admitResult(const QList<QString> &uuids);
    void admitResult(std::vector<std::unique_ptr<IPrimitive> > &ents);

private:
    bool isStatusOk = false;

    static QString serverName;
    static QString httpVersion;
    static QString nextLn;

    QList<QString> strings;
    std::vector<std::unique_ptr<IPrimitive> > entities;

    // 1 step
    void createStartLine(int status);
    // 2 step
    void createHeaders(const HttpParser &parser);
    // 3 step
    void createMessage(const HttpParser &parser);

    QString bound = "separator";
};

//! @} server_part

}

#endif // HTTPRESPONSE_H
