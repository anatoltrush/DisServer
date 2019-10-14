#include "HttpParser.h"

dis::HttpParser::HttpParser(){}

void dis::HttpParser::parse(const QByteArray &data){
    QString allData(data);
    // TODO: check errors

    // 1) separate into two parts (st+headers and message)
    QStringList startHdrs_Msg = allData.split("\r\n\r\n");
    // TODO: check errors
    QString startHdrs = startHdrs_Msg.front();
    this->message_body = startHdrs_Msg.back();

    // 2) separate into two parts (start line and headers)
    QStringList hdrs = startHdrs.split("\r\n");

    // 2.1) start line
    this->starting_line = hdrs.front();

    // 2.2) headers
    for(int i = 1; i < hdrs.size(); i++){
        QStringList hdrLst = hdrs[i].split(": ");
        this->headers.insert(hdrLst.front(), hdrLst.back());
    }

    // 3) first string
    QStringList startWrds = this->starting_line.split(" ");
    this->method = startWrds[0];
    this->address = startWrds[1];
    this->httpVers = startWrds[2];

    // 4) entity & function
    QStringList entFunc = this->address.split("/");
    if(entFunc.size() > 1) this->entity = entFunc[1];
    if(entFunc.size() > 2) this->function = entFunc[2];
}
