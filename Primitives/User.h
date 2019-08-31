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
    //! full constructor
    //TODO: impl

    // COMMON PROPERTY
    QUuid uuid = QUuid::createUuid();
    QString name;
    QString surname;
    QString country;
    QString email;
    QList<QString> IPs;

    QDate time_birth;
    int sex = 0;

    // SPECIAL PROPERTY
    int score = 0;
    int level = 0;
    QDate time_registration;
    QDate last_active;
    QString nickName;
    QString login;
    QString password;

    std::vector<dis::Discussion> discsGood;
    std::vector<dis::Discussion> discsBad;
    std::vector<dis::Purchase> purchases;

    void fillData(const QSqlQuery& query, const QSqlRecord& rec);

private:
};
}

#endif // USER_H

// TODO: validations
