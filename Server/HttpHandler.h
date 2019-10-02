#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H

#include "HttpParser.h"
#include "../DB_API/DBController.h"

// TODO: define errors and statuses

namespace dis{
class HttpHandler
{
public:
    HttpHandler();

    void handle(const HttpParser &parser, const DBController &dbcntr);
};
}

#endif // HTTPHANDLER_H
