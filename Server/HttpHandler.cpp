#include "HttpHandler.h"

dis::HttpHandler::HttpHandler(){}

void dis::HttpHandler::handle(const HttpParser &parser, const DBController &dbcntr, HttpResponse &response){
    std::vector<std::unique_ptr<IPrimitives>> entities;
    QList<QString> uuids;

    // GET
    if(parser.method == QString(VERB_GET)){
        for(const auto &dbApi : dbcntr.dbAPIs){
            if(dbApi->typeApi == parser.entity){
                code = dbApi->getFunction(parser.function, entities, uuids);
                if(code == HTTP_OK){
                    response.admitResult(std::move(entities));
                    response.admitResult(uuids);
                    break;
                }
            }
        }
    }
    // POST
    if(parser.method == VERB_POST){

    }
    // PATCH
    if(parser.method == VERB_PATCH){

    }
    // DELETE
    if(parser.method == VERB_DELETE){

    }
    // else...
}
