#ifndef CLIENT_H
#define CLIENT_H

#include <QDate>

namespace dis{
//! @addtogroup entities
//! @{
class Client
{
public:
    Client() = default;
    Client(const QString &_uuid, const QString &autrTkn, const QDateTime &tm);
    ~Client() = default;

    QString uuid;
    QString authorToken;
    QDateTime lastRequestTime;
};
//! @} entities
}

#endif // CLIENT_H
