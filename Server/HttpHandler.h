#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H

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

    int code = -666;

    void handle(const HttpParser &parser, const DBController &dbcntr, HttpResponse &response);
};

//! @} server_part

}

#endif // HTTPHANDLER_H
