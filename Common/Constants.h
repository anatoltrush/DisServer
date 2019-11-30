#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

#define DB_NAME         "Disput_db"
#define DB_NAME_LOG     "Disput_db_log"

constexpr int uuidSize = 38; // size of UUID string

#define IMG_FORMAT_JPG  "JPG"

//{ Names of tables
#define TABLE_ANSWERS       "Answers"
#define TABLE_COMMENTS      "Comments"
#define TABLE_DISPUTES      "Disputes"
#define TABLE_IMAGES        "Images"
#define TABLE_USERS         "Users"
//}

// Entities for API by typeNames
#define API_TYPE_ANSWERS    "answers"
#define API_TYPE_COMMENTS   "comments"
#define API_TYPE_DISPUTES   "disputes"
#define API_TYPE_IMAGES     "images"
#define API_TYPE_USERS      "users"

// Functions names
#define KW_FUNC_REGISTRATION    "registration"
#define KW_FUNC_LOGIN           "login"
#define KW_FUNC_LOGOUT          "logout"

// In headers
#define HDR_KW_AUTHORIZATION    "Authorization"
#define HDR_KW_PSWRD            "Password"
#define HDR_KW_CONTENT_TYPE     "Content-Type"

//! @group server_status
//! @{
#define HTTP_OK                     200
#define HTTP_CREATED                201 // (PUT || POST) CREATED GOOD

#define HTTP_BAD_REQUEST            400 // (PUT || POST) BAD FORMAT OR LOST
#define HTTP_UNAUTHORIZED           401
#define HTTP_FORBIDDEN              403
#define HTTP_NOT_FOUND              404 // BAD URL
#define HTTP_METHOD_NOT_ALLOWED     405 // BAD API
#define HTTP_CONFLICT               409 // REPEATED RECORD
#define HTTP_UNPROCESSABLE_ENTITY   422 // Unprocessable Entity

#define HTTP_INTERNAL_SERVER_ERROR  500 // UNDEFINED
#define HTTP_NOT_IMPLEMENTED        501
#define HTTP_WEB_SERVER_IS_DOWN     521
//! @} server_status

//! @group server_status
//! @{
#define VERB_GET        "GET"
#define VERB_POST       "POST"
#define VERB_PATCH      "PATCH"
#define VERB_DELETE     "DELETE"
#define VERB_PUT        "PUT"
#define VERB_OPTION     "OPTION"
#define VERB_HEAD       "HEAD"
//! @} server_status

namespace dis {
    QString getReasonPhrase(int code);
}

//typedef enum _HTTP_VERB {
//  HttpVerbUnparsed = 0,
//  HttpVerbUnknown,HttpVerbInvalid,HttpVerbOPTIONS,HttpVerbGET,HttpVerbHEAD,HttpVerbPOST,HttpVerbPUT,HttpVerbDELETE,
//  HttpVerbTRACE,HttpVerbCONNECT,HttpVerbTRACK,HttpVerbMOVE,HttpVerbCOPY,HttpVerbPROPFIND,HttpVerbPROPPATCH,HttpVerbMKCOL,HttpVerbLOCK,
//  HttpVerbUNLOCK,HttpVerbSEARCH,HttpVerbMaximum
//} HTTP_VERB;

#endif // CONSTANTS_H
