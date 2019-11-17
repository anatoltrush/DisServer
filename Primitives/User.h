#ifndef USER_H
#define USER_H

#include "IPrimitive.h"

#define PROP_USR_UUID       "UUID"
#define PROP_USR_NAME       "Name"
#define PROP_USR_SNAME      "Surname"
#define PROP_USR_CNTRY      "Country"
#define PROP_USR_CITY       "City"
#define PROP_USR_EMAIL      "Email"
#define PROP_USR_SEX        "Sex"
#define PROP_USR_PREF       "Preference"
#define PROP_USR_NICK       "Nick_name"
#define PROP_USR_PSWRD      "Password"
#define PROP_USR_MNY        "Money"
#define PROP_USR_SCORE      "Score"
#define PROP_USR_TIME_BRTH  "Time_birth"
#define PROP_USR_TIME_REG   "Time_register"
#define PROP_USR_AVTR       "Avat_data"
#define PROP_USR_W          "Avat_width"
#define PROP_USR_H          "Avat_height"
#define PROP_USR_FRMT       "Format"

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

class User : public IPrimitive // TODO: fill all fields
{
public:
    User();
    ~User() override;

    QString uuid = QUuid::createUuid().toString();
    QString name;
    QString surname;

    QString country;
    QString city;

    QString email;
    std::vector<QString> IPs;

    Sex sex = Sex::NA;
    Sex preference = Sex::NA;

    QString nickName;
    QString password;
    int money = 0;
    int status = 0; // confirmed, banned or else / need?
    int score = 0;
    int level = 0; // need?

    QDateTime time_birth;
    QDateTime time_registration;
    QDateTime time_last_active; // need?

    // Avatar (image)
    QByteArray avtr_data;
    int avtr_w = 0;
    int avtr_h = 0;
    QString format = IMG_FORMAT_JPG;
    // 21

    QString getUUID() const override {return uuid;}
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
