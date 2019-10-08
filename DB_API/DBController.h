#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include "UserAPI.h"
#include "DiscussionAPI.h"
#include "PurchaseAPI.h"
#include "CommentAPI.h"
#include "ImageAPI.h"
#include "AnswerAPI.h"

namespace dis{

//! @addtogroup database_api
//! @{

class DBController
{
public:
    DBController();
    ~DBController();

    QSqlDatabase dataBase;

    //! string for test "DRIVER={SQL Server};SERVER=250PC;DATABASE=Disput_db;Trusted_Connection=yes;"
    bool connect(const QString& connectString);
    void disconnect();

    //! from string (if got string)
    bool doQuery(const QString& string); // FIXME: no need, delete later

    AnswerAPI answerAPI;
    UserAPI userAPI;
    DiscussionAPI discussionAPI;
    PurchaseAPI purchaseAPI;
    CommentAPI commentAPI;
    ImageAPI imageAPI;

private:
    char separToken = '_';

    bool connected = false;
    QString connString;

    QStringList words;

    //!make right query
    bool parseQuery(); // FIXME: no need, delete later

    //! make User from ByteArray
    //! EXAMPLE!!!
    dis::User getUserFromWords();
};

//! @} database_api

}

#endif // DBCONTROLLER_H
