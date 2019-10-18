#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#define IS_HTML

#include "Constants.h"
#include "HttpParser.h"
#include "../Primitives/IPrimitives.h"
#include "../Deploy/Deploy_HTML.h"

namespace dis{

//! @addtogroup server_part
//! @{

class HttpResponse
{
public:
    HttpResponse();

    QByteArray responseQBA;

    QString registrKey;

    void createResponse(const HttpParser &parser, int code);

    void admitResult(const QList<QString> &uuids);
    void admitResult(std::vector<std::unique_ptr<IPrimitives> > &ents);

private:
    static QString serverName;
    static QString httpVersion;
    static QString nextLn;

    QList<QString> uuids;
    std::vector<std::unique_ptr<IPrimitives> > entities;

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
    void createMessage(const HttpParser &parser);

    QString bound = "separator";
};

//! @} server_part

}
// TODO: parse message body
#endif // HTTPRESPONSE_H
