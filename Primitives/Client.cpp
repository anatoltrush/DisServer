#include "Client.h"

dis::Client::Client(const QString &_uuid, const QString &autrTkn, const QDateTime &tm):
    uuid(_uuid), authorToken(autrTkn), lastRequestTime(tm){}
