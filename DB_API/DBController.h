#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include "UserAPI.h"
#include "DiscussionAPI.h"
#include "PurchaseAPI.h"
#include "CommentAPI.h"
#include "ImageAPI.h"
#include "AnswerAPI.h"

namespace dis{
class DBController
{
public:
    DBController();
    ~DBController();

    QSqlDatabase dataBase;

    //! string for test "DRIVER={SQL Server};SERVER=250PC;DATABASE=Disput_db;Trusted_Connection=yes;"
    bool connect(const QString& connectString);
    void disconnect();

    //! from ByteArray (start method)
    bool doQuery(const QByteArray& array);

    //! from string (if got string)
    bool doQuery(const QString& string);

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

    //! fill "words"
    bool parseByteArray(const QByteArray& array); // FIXME: no need, delete later

    //! make User from ByteArray
    dis::User getUserFromWords(); // FIXME: no need, delete later
};
}

#endif // DBCONTROLLER_H
