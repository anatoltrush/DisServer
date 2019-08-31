#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include "UserAPI.h"
#include "DiscussionAPI.h"
#include "PurchaseAPI.h"

namespace dis{
class DBController
{
public:
    DBController();

    QSqlDatabase dataBase;

    bool connect(const QString& connectString);
    void disconnect();

    UserAPI userAPI;
    DiscussionAPI discussionAPI;
    PurchaseAPI purchaseAPI;

    ~DBController();

private:    
    bool connected = false;

    QStringList words;

    //!make right query
    bool parseQuery();

    //! fill "parsedWords"
    bool parseByteArray(const QByteArray& array);

    //! make User from ByteArray
    dis::User getUserFromWords();
};
}

#endif // DBCONTROLLER_H

// TODO: check words size (validation of incoming message)
