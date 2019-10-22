#include "HttpParser.h"

dis::HttpParser::HttpParser(){}

void dis::HttpParser::parse(const QByteArray &data){
    basicParse(data);

    if(method == QString(VERB_GET)) getParse();
    if(method == QString(VERB_POST)) postParse();
    if(method == QString(VERB_PATCH)) patchParse();
    if(method == QString(VERB_DELETE)) deleteParse();
    if(method == QString(VERB_OPTION)) optionParse();
    if(method == QString(VERB_PUT)) optionPut();
    if(method == QString(VERB_HEAD)) optionHead();
}

void dis::HttpParser::basicParse(const QByteArray &data){
    QString message_body;
    QString allData(data);
    // TODO: check errors

    // 1) separate into two parts (st+headers and message)
    QStringList startHdrs_Msg = allData.split("\r\n\r\n");
    // TODO: check errors
    QString startHdrs = startHdrs_Msg.front();
    message_body.clear();
    for(int i = 1; i < startHdrs_Msg.size(); i++)
        message_body.append(startHdrs_Msg[i]);

    // 2) separate into two parts (start line and headers)
    QStringList hdrs = startHdrs.split("\r\n");

    // 2.1) start line
    this->starting_line = hdrs.front();

    // 2.2) first string
    QStringList startWrds = this->starting_line.split(" ");
    this->method = startWrds[0];
    this->address = startWrds[1];
    this->httpVers = startWrds[2];

    // 2.3) entity & function
    QStringList entFunc = this->address.split("/");
    if(entFunc.size() > 1) this->entity = entFunc[1];
    if(entFunc.size() > 2) this->function = entFunc[2];

    // 3) headers
    for(int i = 1; i < hdrs.size(); i++){
        QStringList hdrLst = hdrs[i].split(": ");
        this->headers.insert(hdrLst.front(), hdrLst.back());
    }

    // 4) Content-type
    for(int i = 0; i < headers.size(); i++){
        if(headers.keys()[i] == KW_CONTENT_TYPE){
            QStringList cntp = headers.values()[i].split("\"");
            this->bound = cntp[1]; // check, may be out of range
        }
    }

    // 5) Separate on blocks
    for(int i = 0; i < headers.size(); i++)
        if(headers.keys()[i] == KW_CONTENT_TYPE)
            blocks = message_body.split("--" + this->bound);
    // DELETE EMPTY BLOCKS
    for(int i = 0; i < blocks.size(); i++)
        if(blocks[i].size() == 0 || blocks[i] == "--"){
            blocks.erase(blocks.begin() + i);
            --i;
        }

    // 6) Authorization
    for(int i = 0; i < headers.size(); i++){
        if(headers.keys()[i] == KW_AUTHORIZATION)
            this->authorToken = headers.values()[i];
    }
}

void dis::HttpParser::getParse(){
    // just cap
    params.insertMulti(KW_UUID_DISPUTE, "{a82a706e-913a-4a32-a1e1-b26d6306edda}");
    // FIXME: do right parse
}

void dis::HttpParser::postParse(){}

void dis::HttpParser::patchParse(){}

void dis::HttpParser::deleteParse(){}

void dis::HttpParser::optionParse(){}

void dis::HttpParser::optionPut(){}

void dis::HttpParser::optionHead(){}
