#ifndef SYSTEMAPI_H
#define SYSTEMAPI_H

#include "../QDisput/Primitives/Client.h"

namespace dis{
class SystemAPI
{
public:
    SystemAPI();

    void sendToAll(const QList<dis::Client> &clients, const QByteArray &message);
};
}

#endif // SYSTEMAPI_H

// TODO: send message to all users
// TODO: whether request is CHAT
