#ifndef DEPLOY_HTML_H
#define DEPLOY_HTML_H

#include <QString>
#include <QFile>
#include <QDebug>

namespace dis{
class Deploy_HTML
{
public:
    Deploy_HTML(bool isStartLoad = false);
    ~Deploy_HTML();

    QByteArray startQBA;

private:
    QFile startFile;

    void loadStartPage(const QString &address = "D:/CODE/DISPUT/QDisput/Deploy/Index.html");
};
}

#endif // DEPLOY_HTML_H
