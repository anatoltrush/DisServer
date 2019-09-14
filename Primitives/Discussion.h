#ifndef DISCUSSION_H
#define DISCUSSION_H

#include <QDate>
#include <QUuid>

namespace dis{
class Discussion
{
public:
    Discussion();
    ~Discussion();

    QString uuid = QUuid::createUuid().toString();
    QString section;
    QString topic;
    QString author;
    QDate time_create;
    int type = -1; // type of discussion
    int level = 0;
    int reward = 0;
    QString languageRegion;
};
}

#endif // DISCUSSION_H
