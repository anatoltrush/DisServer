#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include "HttpHandler.h"

// TODO: define errors and statuses

namespace dis{
class HttpResponse
{
public:
    HttpResponse();

    void createResponse(const HttpHandler &handler);

    const QByteArray &toQByteArray();

private:
    QByteArray responseQBA;
};
}

#endif // HTTPRESPONSE_H
