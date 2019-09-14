#ifndef USER_H
#define USER_H

#include <QDate>
#include <QUuid>
#include <QtSql>

#include "Discussion.h"
#include "Purchase.h"

namespace dis{
class User
{
public:
    //! short constructor
    User(); // PHOTO?
    ~User();
    //! full constructor
    //TODO: implement constructor if need

    // COMMON PROPERTY
    QString uuid = QUuid::createUuid().toString();
    QString name;
    QString surname;

    QString country;
    QString city;

    QString email;
    QList<QString> IPs;

    QDate time_birth;
    int sex = 0;    

    // SPECIAL PROPERTY
    QString nickName;
    QString login;
    QString password;
    int role = -1;
    int status = -1; // confirmed, banned or else
    int score = 0;
    int level = 0;
    QDate time_registration;
    QDate time_last_active;

    std::vector<dis::Discussion> discsGood;
    std::vector<dis::Discussion> discsBad;
    std::vector<dis::Purchase> purchases;

    bool isAuthorized = false;

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec);
    void fillByList(const QList<QString> &words, bool isFromParse = false);

private:
};
}

#endif // USER_H

// TODO: validations some parameters
