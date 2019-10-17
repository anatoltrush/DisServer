#ifndef DISCUSSION_H
#define DISCUSSION_H

#include <QUuid>
#include <QImage>
#include <QtSql>

#include "IPrimitives.h"

namespace dis{
//! @addtogroup entities
//! @{
class Discussion : public IPrimitives
{
public:
    Discussion();
    ~Discussion() override;

    QString uuid = QUuid::createUuid().toString();
    QString uuid_author;
    QString section;
    QString topic;    
    QDateTime time_created;
    int type = -1; // type of discussion
    int step = 0;
    int reward = 0;
    QString languageRegion;
    QString text;
    int voted;
    int maxVoters;
    QByteArray icon_data;
    int img_w;
    int img_h;
    // 15

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) override;

private:
    QByteArray createMessageBody(const std::vector<std::unique_ptr<IPrimitives>> &entities, const QString &separ) override;
    QByteArray createMessageBodyHtml() override;
};
//! @} entities
}

#endif // DISCUSSION_H
