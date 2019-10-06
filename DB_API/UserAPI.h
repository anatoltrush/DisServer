#ifndef USERAPI_H
#define USERAPI_H

#include "../QDisput/Primitives/User.h"

namespace dis{
class UserAPI
{
public:
    UserAPI();
    ~UserAPI();

    bool addUser(const QSqlDatabase& db, const dis::User &user);
    bool deleteUser(const QSqlDatabase& db, const QString &uuid);
    bool updateUser(const QSqlDatabase& db, const QString &uuid, const dis::User &newData);
    bool getUserByUuid(const QSqlDatabase& db, const QString &uuid, dis::User &user);

    bool getUsers(const QSqlDatabase& db, QList<dis::User>& users);

private:
    QString tableName = "Users";
};
}

#endif // USERAPI_H
