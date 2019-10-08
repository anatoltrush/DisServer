#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H

#include "HttpParser.h"
#include "HttpResponse.h"
#include "../DB_API/DBController.h"

// TODO: define errors and statuses

namespace dis{

//! @addtogroup server_part
//! @{

class HttpHandler
{
public:
    HttpHandler();

    void handle(const HttpParser &parser, const DBController &dbcntr, HttpResponse &response);
};

//! @} server_part

}

#endif // HTTPHANDLER_H
