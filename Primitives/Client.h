#ifndef CLIENT_H
#define CLIENT_H

#include <QDate>
#include <QTcpSocket>

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

    QDateTime connection_time;
    QTcpSocket *socket;
};
//! @} entities
}

#endif // CLIENT_H
