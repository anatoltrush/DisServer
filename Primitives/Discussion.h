#ifndef DISCUSSION_H
#define DISCUSSION_H

#include <QDate>
#include <QUuid>

namespace dis{
class Discussion
{
public:
    Discussion();

    QUuid uuid = QUuid::createUuid();
    QString section;
    QString topic;
    QString author;
    QDate time_create;
    int level = 0;
    int reward = 0;
};
}

#endif // DISCUSSION_H
