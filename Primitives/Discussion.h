#ifndef DISCUSSION_H
#define DISCUSSION_H

#include "IPrimitives.h"

#define PROP_DISP_UUID          "UUID"
#define PROP_DISP_UUID_AUTHOR   "UUID_author"
#define PROP_DISP_SECTION       "Section"
#define PROP_DISP_TOPIC         "Topic"
#define PROP_DISP_TIME_CRTD     "Time_created"
#define PROP_DISP_TYPE          "Type"
#define PROP_DISP_STEP          "Step"
#define PROP_DISP_REWARD        "Reward"
#define PROP_DISP_LANG_REG      "Lang_region"
#define PROP_DISP_TEXT_DATA     "Text_data"
#define PROP_DISP_VOTED         "Voted"
#define PROP_DISP_MAX_VOTERS    "MaxVoters"
#define PROP_DISP_ICON          "Icon_data"
#define PROP_DISP_W             "Img_width"
#define PROP_DISP_H             "Img_height"

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
    int voted = 0;
    int maxVoters = 0;
    QByteArray icon_data;
    int img_w = 0;
    int img_h = 0;
    // 15

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) override;
    void fillByParse(const QVariantMap &params) override;

private:
    QByteArray createMessageBody(const QString &separ) override;
    QByteArray createMessageBodyHtml() override;
};
//! @} entities
}

#endif // DISCUSSION_H
