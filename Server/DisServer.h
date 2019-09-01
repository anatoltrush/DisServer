#ifndef DISSERVER_H
#define DISSERVER_H

#include <QTcpServer>
#include <QTcpSocket>

#define OK                  200
#define ERR_CREATED         201 // (PUT || POST) CREATED GOOD
#define ERR_BAD_REQUEST     400 // (PUT || POST) BAD FORMAT OR LOST
#define ERR_UNAUTHORIZED    401
#define ERR_NOT_FOUND       404 // BAD URL
#define ERR_METHOD_NOT_ALLOWED  405 // BAD API
#define ERR_CONFLICT        409 // REPEATED RECORD
#define ERR_INTERNAL_SERVER_ERROR   500 // UNDEFINED

namespace dis{
class DisServer
{
public:
    DisServer();
};
}

#endif // DISSERVER_H
