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
    ~DBController();

    QSqlDatabase dataBase;

    bool connect(const QString& connectString);
    void disconnect();

    //! from ByteArray
    bool doQuery(const QByteArray& array);
    //! from JSON file
    bool doQuery();

    UserAPI userAPI;
    DiscussionAPI discussionAPI;
    PurchaseAPI purchaseAPI;

private:    
    bool connected = false;
    QString connString;

    QStringList words;

    //!make right query
    bool parseQuery();

    //! fill "words"
    bool parseByteArray(const QByteArray& array);

    //! make User from ByteArray
    dis::User getUserFromWords();
};
}

#endif // DBCONTROLLER_H
