#ifndef DISCUSSION_H
#define DISCUSSION_H

#include <QUuid>
#include <QImage>
#include <QtSql>

namespace dis{
class Discussion
{
public:
    Discussion();
    ~Discussion();

    QString uuid = QUuid::createUuid().toString();
    QString section;
    QString topic;
    QString author_uuid;
    QString time_create;
    QImage icon;
    int type = -1; // type of discussion
    int step = 0;
    int reward = 0;
    QString languageRegion;    

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec);
};
}

#endif // DISCUSSION_H
