#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include "HttpHandler.h"

// TODO: define errors and statuses

namespace dis{
class HttpResponse
{
public:
    HttpResponse();

    void createResponse(const HttpHandler &handler, const HttpParser &parser);

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
}

#endif // HTTPRESPONSE_H
