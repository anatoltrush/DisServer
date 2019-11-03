#include "HttpHandler.h"

dis::HttpHandler::HttpHandler(){}

void dis::HttpHandler::handle(const HttpParser &parser, const DBController &dbcntr, HttpResponse &response, QList<Client> &clients){
    // NOT AUTHORIZED REQUESTS

    UserAPI userAPI;
    if(userAPI.typeApi == parser.entity){
        // REGISTRATION
        if(parser.method == VERB_POST && parser.function == KW_FUNC_REGISTRATION){
            IPrimitive* primit = parser.object.get();
            User newUser = *static_cast<User*>(primit);

            bool isExsist = false;
            // NOTE: e-mail check
            bool checkEmail = sysAPI.isEmailExsist(dbcntr.dataBase, userAPI.tableName, newUser.email, isExsist);
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
                clients.push_back(Client(newUser.uuid, token, QDateTime::currentDateTime()));
                status = HTTP_OK;
                return;
            }
            else{
                status = HTTP_INTERNAL_SERVER_ERROR;
                return;
            }
        }
        // LOG IN
        if(parser.method == VERB_GET && parser.function == KW_FUNC_LOGIN){
            QString userUuid;
            bool isExsist = sysAPI.checkPswrd(dbcntr.dataBase, userAPI.tableName, parser.pswrd, userUuid);
            if(isExsist && !userUuid.isEmpty()){
                QString token = QUuid::createUuid().toString();
                response.authToken = token;
                if(!sysAPI.isAlreadyIn(clients, userUuid)){
                    clients.push_back(Client(userUuid, token, QDateTime::currentDateTime()));
                    status = HTTP_OK;
                    return;
                }
                else{
                    status = HTTP_FORBIDDEN;
                    return;
                }
            }
            else{
                status = HTTP_UNAUTHORIZED;
                return;
            }
        }
        // LOG OUT
        if(parser.method == VERB_GET && parser.function == KW_FUNC_LOGOUT){
            sysAPI.logOut(clients, parser.authorToken);
            status = HTTP_OK;
            return;
        }
    }

    // IS AUTHORIZED
    if(parser.authorToken != "godOfPhp"){ // FIXME: temporary password, delete later
        bool isAuth = sysAPI.isAuthorized(clients, parser.authorToken, currentUser);
        if(!isAuth){
            status = HTTP_UNAUTHORIZED;
            return;
        }
    }

    std::vector<std::unique_ptr<IPrimitive>> entities;
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
        for(const auto &dbApi : dbcntr.dbAPIs){
            if(dbApi->typeApi == parser.entity){
                status = dbApi->postFunction(parser);
                break;
            }
            else{
                status = HTTP_UNPROCESSABLE_ENTITY;
            }
        }
    }
    // PATCH
    if(parser.method == VERB_PATCH){
        for(const auto &dbApi : dbcntr.dbAPIs){
            if(dbApi->typeApi == parser.entity){
                bool isUserGranted = sysAPI.isGranted(currentUser, parser.object);
                if(isUserGranted){
                    status = dbApi->patchFunction(parser);
                    break;
                }
                else{
                    status = HTTP_UNAUTHORIZED;
                    break;
                }
            }
            else{
                status = HTTP_UNPROCESSABLE_ENTITY;
            }
        }
        // use parser.object
        // TODO: check WHO CAN PATCH (only owner)
    }
    // DELETE
    if(parser.method == VERB_DELETE){
        for(const auto &dbApi : dbcntr.dbAPIs){
            if(dbApi->typeApi == parser.entity){
                bool isUserGranted = sysAPI.isGranted(currentUser, parser.object);
                if(isUserGranted){
                    status = dbApi->deleteFunction(parser);
                    break;
                }
                else{
                    status = HTTP_UNAUTHORIZED;
                    break;
                }
            }
            else{
                status = HTTP_UNPROCESSABLE_ENTITY;
            }
        }
    }
    // else... (OPTIONS, PUT and other)
}
