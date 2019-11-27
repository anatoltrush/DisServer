#include "HttpParser.h"

void dis::HttpParser::parse(const QByteArray &data){
    basicParse(data);
    validateParams();
    if(status != HTTP_OK) return;

    if(method == QString(VERB_GET)) getParse();
    if(method == QString(VERB_POST)) postParse();
    if(method == QString(VERB_PATCH)) patchParse();
    if(method == QString(VERB_DELETE)) deleteParse();
    if(method == QString(VERB_OPTION)) optionParse();
    if(method == QString(VERB_PUT)) putParse();
    if(method == QString(VERB_HEAD)) headParse();
}

void dis::HttpParser::setStatus(int stat, const QString &msg){
    status = stat;
    statMsg = msg;
}

void dis::HttpParser::basicParse(const QByteArray &data){
    QString message_body;
    QString allData(data);
    // check
    if(data.isEmpty()){
        setStatus(HTTP_BAD_REQUEST, "PARSER ERROR: Empty request data.");
        return;
    }

    // 1) separate into two parts (st+headers and message)
    QStringList startHdrs_Msg = allData.split("\r\n\r\n");

    QString startHdrs = startHdrs_Msg.front();
    message_body.clear();
    for(int i = 1; i < startHdrs_Msg.size(); i++){
        message_body.append(startHdrs_Msg[i]);
        message_body.append("\r\n\r\n"); // resurrect deleted
    }

    // 2) separate into two parts (start line and headers)
    QStringList hdrs = startHdrs.split("\r\n");

    // 2.1) start line
    this->starting_line = hdrs.front();

    // 2.2) first string
    QStringList startWrds = this->starting_line.split(" ");
    // check
    if(startWrds.size() < 3){
        setStatus(HTTP_BAD_REQUEST, "PARSER ERROR: Bad start line parse.");
        return;
    }
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
    // check
    if(headers.isEmpty()){
        setStatus(HTTP_BAD_REQUEST, "PARSER ERROR: Empty headers.");
        return;
    }

    // 4) Content-type/bound
    for(int i = 0; i < headers.size(); i++){
        if(headers.keys()[i] == HDR_KW_CONTENT_TYPE){
            QStringList cntType = headers.values()[i].split("\"");
            // check
            if(cntType.size() < 2){
                setStatus(HTTP_BAD_REQUEST, "PARSER ERROR: bound searching.");
                return;
            }
            this->bound = cntType[1]; // check, may be out of range
        }
    }

    // 5) Separate on blocks
    for(int i = 0; i < headers.size(); i++)
        if(headers.keys()[i] == HDR_KW_CONTENT_TYPE)
            blocks = message_body.split("--" + this->bound);
    // delete empty blocks
    for(int i = 0; i < blocks.size(); i++)
        if(blocks[i].size() == 0 || blocks[i] == "--\r\n\r\n"){
            blocks.erase(blocks.begin() + i);
            --i;
        }
    // delete begs & ends
    for(auto &block : blocks){
        block.remove(0, 2); // begs
        int bl_sz = block.size();
        block.remove(bl_sz-2, 2); // ends
    }

    // 6) Authorization
    for(int i = 0; i < headers.size(); i++){
        if(headers.keys()[i] == HDR_KW_AUTHORIZATION)
            this->authorToken = headers.values()[i];
    }

    // 7) Pswrd
    for(int i = 0; i < headers.size(); i++){
        if(headers.keys()[i] == HDR_KW_PSWRD)
            this->pswrd = headers.values()[i];
    }

    // 8) fill params
    for(const auto &block : blocks){
        QPair<QString, QVariant> record = parseBlock(block);
        params.insertMulti(record.first, record.second);
    }

    // if all ok
    setStatus(HTTP_OK, "OK");
}

void dis::HttpParser::getParse(){}

void dis::HttpParser::postParse(){
    getPrimitive(object, entity);
    object->fillByParse(params);
}

void dis::HttpParser::patchParse(){
    getPrimitive(object, entity);
    object->fillByParse(params);
}

void dis::HttpParser::deleteParse(){}

void dis::HttpParser::optionParse(){}

void dis::HttpParser::putParse(){
    getPrimitive(object, entity);
    object->fillByParse(params);
}

void dis::HttpParser::headParse(){}

void dis::HttpParser::validateParams(){
    QString badSymb = " ";
    for(int i = 0; i < params.size(); i++){
        QString key = params.keys()[i];
        if(key.contains(badSymb)){
            setStatus(HTTP_BAD_REQUEST, "PARSER ERROR: Bad params.");
        }
    }
}

QPair<QString, QVariant> dis::HttpParser::parseBlock(const QString &block){
    QPair<QString, QVariant> res;
    // do check (assert)
    QStringList name_type_data = block.split("\r\n\r\n");
    QStringList name_type = name_type_data[0].split("\r\n");

    // name
    QString _n = "name=\"";
    QString name;
    int name_pos = name_type[0].indexOf(_n);
    if(name_pos >= 0){
        for(int i = name_pos + _n.size(); i < name_type[0].size(); i++){
            QChar symb = name_type[0][i];
            if(symb == '"') break;
            name.append(symb);
        }
    }

    // format
    QStringList type_format = name_type.back().split(": ");
    QString format_full = type_format.back();
    QString format_short = format_full.split("/")[0];

    // --- return ---
    if(format_short == "text")
        res = qMakePair(name, name_type_data[1]);
    if(format_short == "image"){
        QByteArray data;
        data.append(name_type_data[1]);
        res = qMakePair(name, data);
    }
    return res;
}

void dis::HttpParser::getPrimitive(std::unique_ptr<IPrimitive> &object, const QString &entity){
    if(entity == API_TYPE_DISPUTES) object = std::make_unique<Discussion>();
    if(entity == API_TYPE_ANSWERS) object = std::make_unique<Answer>();
    if(entity == API_TYPE_COMMENTS) object = std::make_unique<Comment>();
    if(entity == API_TYPE_IMAGES) object = std::make_unique<Image>();
    if(entity == API_TYPE_USERS) object = std::make_unique<User>();
}
