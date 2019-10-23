#include "HttpHandler.h"

dis::HttpHandler::HttpHandler(){}

void dis::HttpHandler::handle(const HttpParser &parser, const DBController &dbcntr, HttpResponse &response, QStringMap &authorTokens){
    // NOT AUTHORIZED REQUESTS

    UserAPI userAPI;
    if(userAPI.typeApi == parser.entity){
        // REGISTRATION
        if(parser.method == VERB_POST && parser.function == KW_REGISTRATION){
            User newUser;
            // TODO: fill user from parser
            QString email = "_t@tut.by"; // FIXME: change

            bool isExsist = false;
            bool checkEmail = sysAPI.isEmailExsist(dbcntr.dataBase, userAPI.tableName, email, isExsist);
            if(!checkEmail){
                status = HTTP_INTERNAL_SERVER_ERROR;
                return;
            }
            if(isExsist){
                status = HTTP_CONFLICT;
                return;
            }

            bool isExec = userAPI.addUser(newUser);
            if(isExec){
                QString token = QUuid::createUuid().toString();
                response.authToken = token;
                authorTokens.insertMulti(newUser.uuid, token); // <uuid, token>
                status = HTTP_OK;
                return;
            }
            else{
                status = HTTP_INTERNAL_SERVER_ERROR;
                return;
            }
        }
        // LOG IN
        if(parser.method == VERB_GET && parser.function == KW_LOGIN){
            QString userUuid;
            QString pswrd = "fff"; // FIXME: change
            bool isExsist = sysAPI.checkPswrd(dbcntr.dataBase, userAPI.tableName, pswrd, userUuid);
            if(isExsist && !userUuid.isEmpty()){
                QString token = QUuid::createUuid().toString();
                response.authToken = token;
                authorTokens.insertMulti(userUuid, token); // <uuid, token>
                status = HTTP_OK;
                return;
            }
            else{
                status = HTTP_UNAUTHORIZED;
                return;
            }
        }
        // LOG OUT
        if(parser.method == VERB_GET && parser.function == KW_LOGOUT){
            sysAPI.logOut(authorTokens, parser.authorToken);
            status = HTTP_OK;
            return;
        }
    }


    // IS AUTHORIZED
    if(parser.authorToken != "godOfPhp"){ // FIXME: delete later
        bool isAuth = sysAPI.isAuthorized(authorTokens, parser.authorToken, currentUser);
        if(!isAuth){
            status = HTTP_UNAUTHORIZED;
            return;
        }
    }

    std::vector<std::unique_ptr<IPrimitives>> entities;
    QList<QString> primitives;

    // GET
    if(parser.method == VERB_GET){
        for(const auto &dbApi : dbcntr.dbAPIs){
            if(dbApi->typeApi == parser.entity){
                status = dbApi->getFunction(parser, entities, primitives);
                if(status == HTTP_OK){
                    response.admitResult(entities);
                    response.admitResult(primitives);
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
        // WARNING: not for User
    }
    // PATCH
    if(parser.method == VERB_PATCH){
        // use parser.object
        // TODO: check WHO CAN PATCH (only owner)
    }
    // DELETE
    if(parser.method == VERB_DELETE){
        // use parser.params
        // TODO: check WHO CAN DELETE (only owner)
    }
    // else... (OPTIONS, PUT and other)
}
