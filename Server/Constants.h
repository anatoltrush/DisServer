#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

//! @group server_status
//! @{
#define HTTP_OK                      200
#define HTTP_CREATED                 201 // (PUT || POST) CREATED GOOD

#define HTTP_BAD_REQUEST             400 // (PUT || POST) BAD FORMAT OR LOST
#define HTTP_UNAUTHORIZED            401
#define HTTP_NOT_FOUND               404 // BAD URL
#define HTTP_METHOD_NOT_ALLOWED      405 // BAD API
#define HTTP_CONFLICT                409 // REPEATED RECORD

#define HTTP_INTERNAL_SERVER_ERROR   500 // UNDEFINED
#define HTTP_NOT_IMPLEMENTED         501
//! @} server_status

//! @group server_status
//! @{
#define VERB_GET        "GET"
#define VERB_POST       "POST"
#define VERB_PATCH      "PATCH"
#define VERB_DELETE     "DELETE"
#define VERB_PUT        "PUT"
#define VERB_OPTION     "OPTION"
//! @} server_status

namespace dis {
    QString getReasonPhrase(int code);
}

// //! @group entities
// //! @{
//#define Answer      answers
//#define Comment     comments
//#define Answer  answers
//#define Answer  answers
//#define Answer  answers
//#define Answer  answers
// //! @} entities

//typedef enum _HTTP_VERB {
//  HttpVerbUnparsed = 0,
//  HttpVerbUnknown,HttpVerbInvalid,HttpVerbOPTIONS,HttpVerbGET,HttpVerbHEAD,HttpVerbPOST,HttpVerbPUT,HttpVerbDELETE,
//  HttpVerbTRACE,HttpVerbCONNECT,HttpVerbTRACK,HttpVerbMOVE,HttpVerbCOPY,HttpVerbPROPFIND,HttpVerbPROPPATCH,HttpVerbMKCOL,HttpVerbLOCK,
//  HttpVerbUNLOCK,HttpVerbSEARCH,HttpVerbMaximum
//} HTTP_VERB;

#endif // CONSTANTS_H
