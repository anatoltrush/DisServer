#ifndef USER_H
#define USER_H

#include <QDateTime>
#include <QUuid>

#include "Discussion.h"
#include "Purchase.h"
#include "IPrimitive.h"

// TODO: #define PROP_USER_UUID"UUID + IN API" // example

namespace dis{
//! @addtogroup entities
//! @{

enum Sex{
    NA = -1,
    Male,
    Female,
    Transgender
    // other if need
};

class User : public IPrimitive
{
public:
    //! short constructor
    User();
    ~User() override;

    // COMMON PROPERTY
    QString uuid = QUuid::createUuid().toString();
    QString name;
    QString surname;

    QString country;
    QString city;

    QString email;
    QList<QString> IPs;

    QDateTime time_birth;
    Sex sex = Sex::NA;
    Sex preference = Sex::NA;

    // SPECIAL PROPERTY
    QString nickName;
    QString login;
    QString password;
    int role = -1;
    int status = -1; // confirmed, banned or else
    int score = 0;
    int level = 0;
    QDateTime time_registration;
    QDateTime time_last_active;
    int money = 0;

    std::vector<dis::Discussion> createdDisps;
    std::vector<dis::Purchase> purchases;   

    QString getAuthor() const override {return uuid;}

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) override;
    void fillByParse(const QVariantMap &params) override;

private:
    QByteArray createMessageBody(const QString &separ) override;
    QByteArray createMessageBodyHtml() override;
};
//! @} entities
}

#endif // USER_H
