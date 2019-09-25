#ifndef CLIENT_H
#define CLIENT_H

#include <QDate>
#include <QTcpSocket>

#include "User.h"

namespace dis{
//! Will be used in chats
class Client : public User
{
public:
    Client();
    ~Client();

    QDate time_last_request;
    QTcpSocket *socket;
};
}

#endif // CLIENT_H
