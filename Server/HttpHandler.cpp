#include "HttpHandler.h"

dis::HttpHandler::HttpHandler(){}

void dis::HttpHandler::handle(const HttpParser &parser, const DBController &dbcntr, HttpResponse &response, QStringMap &authorTokens){
    // if LOG OUT
//    sysAPI.logOut(authorTokens, parser.authorToken);

    QString regWord = "registr"; // FIXME: registr keyword
    if(parser.authorToken == regWord){ // here you can only registrate, nothing more
        // checks
        UserAPI userApi;
//        userApi.addUser(/**/);
        // if all ok - registr, write in response key & out
        // else - error & out
        return;
    }

    if(parser.authorToken != "godOfPhp"){ // FIXME: delete later
        bool isAuth = sysAPI.isAuthorized(authorTokens, parser.authorToken);
        if(!isAuth){
            status = HTTP_UNAUTHORIZED;
            return;
        }
    }

    std::vector<std::unique_ptr<IPrimitives>> entities;
    QList<QString> uuids;

    // GET
    if(parser.method == QString(VERB_GET)){
        for(const auto &dbApi : dbcntr.dbAPIs){
            if(dbApi->typeApi == parser.entity){
                status = dbApi->getFunction(parser.function, entities, uuids, parser.params);
                if(status == HTTP_OK){
                    response.admitResult(entities);
                    response.admitResult(uuids);
                }
                break;
            }
            else{
                status = HTTP_UNPROCESSABLE_ENTITY;
            }
        }
    }
    // POST
    if(parser.method == VERB_POST){
        // use parser.object
    }
    // PATCH
    if(parser.method == VERB_PATCH){
        // use parser.object
    }
    // DELETE
    if(parser.method == VERB_DELETE){
        // use parser.params
    }
    // else... (OPTIONS, PUT and other)
}
