#ifndef DISSERVER_H
#define DISSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

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
    QList<QTcpSocket*> sockets;

    QList<Client> clients;

    QTimer* timerKick;
    QTimer* timerShrink;

    DBController dbcntr;

    QString defConnStr = "DRIVER={SQL Server};SERVER=250PC;DATABASE=" + QString(DB_NAME) + ";Trusted_Connection=yes;";

public slots:
    // server slots
    void slotNewConnection();
    void slotReadyRead();
    void slotClientDisconnected();
    void slotSocketDeleted();

    // timer slots
    void slotTickKick();
    void slotTickShrink();
};
//! @} server_part
}
#endif // DISSERVER_H
