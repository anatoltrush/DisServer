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

    //! fill "parsedWords"
    bool parseByteArray(const QByteArray& array);

    //!make right query
    bool parseQuery();

    UserAPI userAPI;
    DiscussionAPI discussionAPI;
    PurchaseAPI purchaseAPI;

    ~DBController();

private:    
    bool connected = false;

    QStringList words;
};
}

#endif // DBCONTROLLER_H

// TODO: check words size (validation of incoming message)
