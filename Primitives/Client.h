#ifndef CLIENT_H
#define CLIENT_H

#include <QDate>
#include <QWebSocket>

#include "User.h"

namespace dis{
class Client : public User
{
public:
    Client();
    ~Client();

    QDate time_last_request;
    QWebSocket *websocket;
};
}

#endif // CLIENT_H
