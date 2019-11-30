#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H

#include "SystemAPI.h"
#include "../Common/Constants.h"
#include "HttpParser.h"
#include "HttpResponse.h"
#include "../DB_API/DBController.h"

namespace dis{

//! @addtogroup server_part
//! @{

class HttpHandler
{
public:
    HttpHandler() = default;
    ~HttpHandler() = default;

    int status = HTTP_BAD_REQUEST;
    QString currentUser;

    SystemAPI sysAPI;

    void handle(const HttpParser &parser, const DBController &dbcntr, HttpResponse &response, QList<Client> &clients);
};

//! @} server_part

}

#endif // HTTPHANDLER_H
