#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QString>
#include "httprequest.h"





int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HttpRequest http_request;



    http_request.makeRequest(QUrl("https://www.mayoclinic.org/diseases-conditions/index?letter=A"));




    return a.exec();
}
