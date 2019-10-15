#include "Deploy_HTML.h"

dis::Deploy_HTML::Deploy_HTML(bool isStartLoad){
    if(isStartLoad)
        loadStartPage();
}

dis::Deploy_HTML::~Deploy_HTML(){
    startFile.close();
}

void dis::Deploy_HTML::loadStartPage(const QString &address){
    startFile.setFileName(address);
    if(startFile.open(QIODevice::ReadOnly)){
        startQBA.append("HTTP/1.0 200 OK\r\n\r\n");
        startQBA.append(startFile.readAll());
        qDebug() << "Start page is loaded";
    }
    else{
        qDebug() << "Error while start page loading";
    }
}
