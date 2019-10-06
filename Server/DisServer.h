#ifndef DISSERVER_H
#define DISSERVER_H

#include <QTcpServer>

#include "Constants.h"
#include "../DB_API/DBController.h"
#include "SystemAPI.h"
#include "HttpParser.h"
#include "HttpResponse.h"
#include "HttpHandler.h"

namespace dis{
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
    void slotReadyRead();
    void slotClientDisconnected();

    void slotSocketDeleted();

signals:

};
}

#endif // DISSERVER_H

// TODO: SEND MESSAGE TO ALL
// TODO: SERVER THREADS
