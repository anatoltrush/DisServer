#ifndef COMMENT_H
#define COMMENT_H

#include <QtSql>

namespace dis{
class Comment
{
public:
    Comment();

    QString uuid = QUuid::createUuid().toString();
    //! dispute OR foto OR other comment
    QString uuid_post;
    QString uuid_author;
    //! can be empty if first comment at all
    QString uuid_receiver;

    QDateTime time_created;

    QString text;

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec);
};
}

#endif // COMMENT_H
