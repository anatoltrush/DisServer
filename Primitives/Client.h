#ifndef CLIENT_H
#define CLIENT_H

#include <QDate>
#include <QTcpSocket>

#include "User.h"

// TODO: #define PROP_USER_UUID"UUID" // example

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
    QTcpSocket *socket; // need for UI
};
//! @} entities
}

#endif // CLIENT_H
