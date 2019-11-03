#ifndef SYSTEMAPI_H
#define SYSTEMAPI_H

#include <QtSql>

#include "../Common/disDefines.h"
#include "../Primitives/Client.h"
#include "../Primitives/IPrimitive.h"

namespace dis{
class SystemAPI
{
public:
    SystemAPI();

    void sendToAll(const QList<dis::Client> &clients, const QByteArray &message);
    void kickByTime(QList<dis::Client> &clients);

    bool isAlreadyIn(const QList<dis::Client> &clients, const QString &userUuid);
    void logOut(QList<dis::Client> &clients, const QString &userToken);
    bool isAuthorized(QList<Client> &clients, const QString &userToken, QString &currUser);
    bool isGranted(const QString &currUser, const std::unique_ptr<IPrimitive> &object) {return currUser == object->getAuthor();}

    bool checkPswrd(const QSqlDatabase &db, const QString &tableName, const QString &pswrd, QString &uuid);
    bool isEmailExsist(const QSqlDatabase &db, const QString &tableName, const QString &Email, bool &isExsist);
};
}

#endif // SYSTEMAPI_H

// TODO: send message to all users
// TODO: whether request is CHAT
