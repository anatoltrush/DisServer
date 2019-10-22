#ifndef CLIENT_H
#define CLIENT_H

#include <QDate>
#include <QTcpSocket>
#include <QHostAddress>

#include "User.h"

namespace dis{

//! @addtogroup entities
//! @{

//! Will be used in chats
class Client
{
public:
    Client();
    ~Client();

    QString uuid;
    QString authorToken;
    QDateTime lastRequestTime;
    QTcpSocket *socket;
};
//! @} entities
}

#endif // CLIENT_H
