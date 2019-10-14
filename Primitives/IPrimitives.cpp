#include "IPrimitives.h"

QString dis::IPrimitives::nextLn = "\r\n";

dis::IPrimitives::IPrimitives(){}

dis::IPrimitives::~IPrimitives(){}

QByteArray dis::IPrimitives::createMessageBody(const QList<QString> &uuids, const QString &separ){
    QList<QString>messStrings;
    for(const auto &uuid : uuids){
        messStrings.push_back("--" + separ);
        messStrings.push_back("Content-Disposition: plain");
        messStrings.push_back("");
        messStrings.push_back(uuid);
    }
    messStrings.push_back("--" + separ + "--");
    // QBA
    QByteArray result;
    for(const auto &str : messStrings){
        QString newStr = str + nextLn;
        result.append(newStr);
    }
    return result;
}

QByteArray dis::IPrimitives::createMessageBodyHtml(const QList<QString> &uuids){
    QString res;
    for(const auto &uuid : uuids){
        res += "<b>";
        res += "<li>";
        res += "&nbsp";
        res += uuid;
        res += "</b>";
        res += "<br>";
        res += "<hr>";
    }
    QByteArray result;
    result.append(res);
    return result;
}
