#ifndef DISSERVER_H
#define DISSERVER_H

#include <QTcpServer>

#include "../Common/disDefines.h"
#include "Constants.h"
#include "../DB_API/DBController.h"
#include "HttpParser.h"
#include "HttpResponse.h"
#include "HttpHandler.h"

namespace dis{

//! @addtogroup server_part
//! @{

class DisServer : public QObject
{
    Q_OBJECT
public:
    DisServer();
    ~DisServer();

    QTcpServer *tcpServer;
    DBController dbcntr;

    QList<Client> clients; // FIXME: remove "Uuid_Token"

    QStringMap Uuid_Token; // <uuid, token> of authorized users // TODO: добавить время авторизации/логина

    int errorStatus = 0;

public slots:
    void slotNewConnection();
    void slotReadyRead();
    void slotClientDisconnected();

    void slotSocketDeleted();

private:
    // TODO; time for kick

};

//! @} server_part

}

#endif // DISSERVER_H

// TODO: SEND MESSAGE TO ALL
