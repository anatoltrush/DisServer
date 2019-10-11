#include "HttpHandler.h"

dis::HttpHandler::HttpHandler(){}

void dis::HttpHandler::handle(const HttpParser &parser, const DBController &dbcntr, HttpResponse &response){
    std::vector<std::unique_ptr<IPrimitives>> entities;
    QList<QString> uuids;

    // GET
    if(parser.method == HTTP_VERB::HttpVerbGET){
        for(const auto &dbApi : dbcntr.dbAPIs){
            if(dbApi->typeApi == parser.entity){
                int result = dbApi->getFunction(parser.method, entities, uuids);
                if(result == 0){
                    response.admitResult(entities);
                    response.admitResult(uuids);
                    break;
                }
            }
        }
    }
    // POST
    if(parser.method == HTTP_VERB::HttpVerbPOST){

    }
    // PATCH
    if(parser.method == HTTP_VERB::HttpVerbPROPPATCH){

    }
    // DELETE
    if(parser.method == HTTP_VERB::HttpVerbDELETE){

    }
    // else...
}
