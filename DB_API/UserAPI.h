#ifndef USERAPI_H
#define USERAPI_H

#include "IdbAPI.h"
#include "../QDisput/Primitives/User.h"

namespace dis{

//! @addtogroup database_api
//! @{

class UserAPI : public IdbAPI
{
public:
    UserAPI();
    ~UserAPI() override;

    bool addUser(const QSqlDatabase& db, const dis::User &user);
    bool deleteUser(const QSqlDatabase& db, const QString &uuid);
    bool updateUser(const QSqlDatabase& db, const QString &uuid, const dis::User &newData);
    bool getUserByUuid(const QSqlDatabase& db, const QString &uuid, dis::User &user);

    bool getUsers(const QSqlDatabase& db, QList<dis::User>& users);

    int getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives>> &primitives, QList<QString> &uuids) override;

private:
};

//! @} database_api

}

#endif // USERAPI_H
