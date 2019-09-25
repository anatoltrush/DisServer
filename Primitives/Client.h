#ifndef CLIENT_H
#define CLIENT_H

#include <QDate>
#include <QTcpSocket>

#include "User.h"

namespace dis{

//! Will be used in chats
class Client
{
public:
    Client();
    ~Client();

    QDateTime connection_time;
    QTcpSocket *socket;
};
}

#endif // CLIENT_H
