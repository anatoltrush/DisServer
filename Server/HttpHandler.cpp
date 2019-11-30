#include "HttpHandler.h"

void dis::HttpHandler::handle(const HttpParser &parser, const DBController &dbcntr, HttpResponse &response, QList<Client> &clients){
    // CHECK PARSER
    if(parser.status != HTTP_OK){
        qDebug() << parser.lastError();
        status = parser.status;
        return;
    }

    // NOTE: NOT AUTHORIZED REQUESTS ARE SITUATED HERE
    UserAPI userAPI;
    if(userAPI.typeApi == parser.entity){
        // REGISTRATION
        if(parser.method == VERB_POST && parser.function == KW_FUNC_REGISTRATION){
            IPrimitive* primit = parser.object.get();
            User newUser = *static_cast<User*>(primit);
            // e-mail check
            bool isExsistEmail = false;
            bool checkEmail = userAPI.isExsistEmail(newUser.email, isExsistEmail);
            if(!checkEmail){
                status = HTTP_INTERNAL_SERVER_ERROR;
                return;
            }
            // nick-name check
            bool isExsistNick = false;
            bool checkNick = userAPI.isExsistNick(newUser.nickName, isExsistNick);
            if(!checkNick){
                status = HTTP_INTERNAL_SERVER_ERROR;
                return;
            }

            // -conclusion-
            if(isExsistEmail || isExsistNick){
                status = HTTP_CONFLICT;
                return;
            }

            // if not duplicate
            bool isExectd = userAPI.addUser(newUser);
            if(isExectd){
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
            bool isExsist = userAPI.checkPswrd(parser.pswrd, userUuid);
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
    if(parser.authorToken != "godOfPhp"){ // FIXME: temporary token, delete later
        bool isAuth = sysAPI.isAuthorized(clients, parser.authorToken, currentUser);
        if(!isAuth){
            status = HTTP_UNAUTHORIZED;
            return;
        }
    }

    // NOTE: AUTHORIZED REQUESTS ARE SITUATED HERE
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
                if(status == HTTP_OK){
                    QString id = parser.object->getUUID();
                    response.admitResult({id});
                }
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
                // get object
                std::unique_ptr<IPrimitive> object;
                bool isObjGot = dbApi->getObjectPart(parser, object);
                if(!isObjGot){
                    status = HTTP_INTERNAL_SERVER_ERROR;
                    return;
                }
                // check rights
                bool isUserVerified = sysAPI.isVerified(currentUser, *object.get());
                if(isUserVerified){
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
    }
    // DELETE
    if(parser.method == VERB_DELETE){
        for(const auto &dbApi : dbcntr.dbAPIs){
            if(dbApi->typeApi == parser.entity){
                // get object
                std::unique_ptr<IPrimitive> object;
                bool isObjGot = dbApi->getObjectPart(parser, object);
                if(!isObjGot){
                    status = HTTP_INTERNAL_SERVER_ERROR;
                    return;
                }
                // check rights
                currentUser = "godOfPhp"; // FIXME: temporary token, delete later
                bool isUserVerified = sysAPI.isVerified(currentUser, *object.get());
                if(isUserVerified){
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
