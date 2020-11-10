/****************************************************************************

****************************************************************************/
#include <QtNetwork>
#include <QUrl>
#include <iostream>
#include "searchengine.h"
#include "logview.h"
#include "searchwindow.h"
#include "loging.h"



SearchEngine::SearchEngine()
{
}



void SearchEngine::makeHttpSearch(std::vector<QStringList> Request, std::vector<QStringList> &ResultList)
{

    QUrl Url_;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;

    Bot bot;
    QString html_content;

    Url_ = Request[0].at(0);

    reply = qnam.get(QNetworkRequest(Url_));

    while(!reply->isFinished())
    {
        qApp->processEvents();

    }

    const QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    if (!redirectionTarget.isNull())
    {
        const QUrl redirectedUrl = Url_.resolved(redirectionTarget.toUrl());

        Url_= redirectedUrl.toString();

        makeHttpSearch(Request, ResultList);
    }
    else
    {
        html_content = reply->readAll();

        bot.searchText(html_content, Request[1], Request[2], ResultList);
    }




}



void SearchEngine::makeFileSearch(std::vector<QStringList> Request, std::vector<QStringList> &ResultList)
{

    QString file_loc = Request.at(0).at(0);
    Bot bot;
    QString file_content;
    QString writable_loc;

    int index = file_loc.indexOf(EXTERNAL_LOC_KEYWORD);

    if(index >= 0) // if the file loc is external from writable
    {
        Loging::printAll(Loging::yellow, "External index: ", index);

        writable_loc = file_loc.mid(file_loc.indexOf(EXTERNAL_LOC_KEYWORD) + strlen(EXTERNAL_LOC_KEYWORD));
        Loging::printAll(Loging::yellow, "Writable_Loc: ", writable_loc.toStdString());

    }
    else        //if file loc is writable loc
    {
        file_loc = file_loc.mid(file_loc.indexOf(FILE_SEARCH_KEYWORD) + strlen(FILE_SEARCH_KEYWORD));
        writable_loc = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        writable_loc += + "/" + file_loc;

    }

    Loging::printAll(Loging::yellow, "File Loc: ", writable_loc.toStdString());

    QFile file(writable_loc);
    file.open(QIODevice::ReadOnly);

    QTextStream s1(&file);
    file_content.append(s1.readAll());

    bot.searchText(file_content, Request[1], Request[2], ResultList);




}



void SearchEngine::searchRequest(std::vector<QStringList> Request, std::vector<QStringList> &ResultList)
{

    if(Request.at(0).at(0).indexOf(HTTPS_SEARCH_KEYWORD) >= 0 ||
            Request.at(0).at(0).indexOf(HTTP_SEARCH_KEYWORD) >= 0)
    {
        makeHttpSearch(Request, ResultList);
    }
    else if(Request.at(0).at(0).indexOf(FILE_SEARCH_KEYWORD) >= 0)
    {
        makeFileSearch(Request, ResultList);
    }

}




