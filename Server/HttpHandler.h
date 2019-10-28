#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H

#include "../Common/disDefines.h"
#include "SystemAPI.h"
#include "Constants.h"
#include "HttpParser.h"
#include "HttpResponse.h"
#include "../DB_API/DBController.h"

namespace dis{

//! @addtogroup server_part
//! @{

class HttpHandler
{
public:
    HttpHandler();

    int status = HTTP_BAD_REQUEST;
    QString currentUser;

    SystemAPI sysAPI;

    void handle(const HttpParser &parser, const DBController &dbcntr, HttpResponse &response, QList<Client> &clients);
};

//! @} server_part

}

#endif // HTTPHANDLER_H
