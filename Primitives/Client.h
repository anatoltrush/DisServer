#ifndef CLIENT_H
#define CLIENT_H

#include <QDate>

// TODO: #define PROP_USER_UUID"UUID" // example

namespace dis{

//! @addtogroup entities
//! @{
class Client
{
public:
    Client();
    Client(const QString &_uuid, const QString &autrTkn, const QDateTime &tm);
    ~Client();

    QString uuid;
    QString authorToken;
    QDateTime lastRequestTime;

//private:
//    Q_DISABLE_COPY(Client)

//signals:
//    void signalUpdTime();

//public slots:
//    void slotUpdTime();
};
//! @} entities
}

#endif // CLIENT_H
