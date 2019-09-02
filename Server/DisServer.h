#ifndef DISSERVER_H
#define DISSERVER_H

#include <QTcpServer>
#include <QTcpSocket>

#include "../DB_API/DBController.h"

#define OK                  200
#define ERR_CREATED         201 // (PUT || POST) CREATED GOOD
#define ERR_BAD_REQUEST     400 // (PUT || POST) BAD FORMAT OR LOST
#define ERR_UNAUTHORIZED    401
#define ERR_NOT_FOUND       404 // BAD URL
#define ERR_METHOD_NOT_ALLOWED  405 // BAD API
#define ERR_CONFLICT        409 // REPEATED RECORD
#define ERR_INTERNAL_SERVER_ERROR   500 // UNDEFINED

namespace dis{

struct Client
{
    Client(){}
    QString uuid;
    QTcpSocket *socket;
};

class DisServer : public QObject
{
    Q_OBJECT
public:
    DisServer();
    ~DisServer();

    QTcpServer *tcpServer;
    dis::DBController dbcntr;

    QList<dis::Client> clients;

    int errorStatus = 0;

public slots:
    void slotNewConnection();

};
}

#endif // DISSERVER_H
