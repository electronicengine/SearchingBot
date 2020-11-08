/****************************************************************************

****************************************************************************/
#include <QtNetwork>
#include <QUrl>
#include <iostream>
#include "httprequest.h"
#include "logview.h"
#include "searchwindow.h"




HttpRequest::HttpRequest(LogView *Log, QObject *parent)
    : QObject(parent)
    , reply(nullptr)
    , httpRequestAborted(false)
    , httpRequestFinished(false)
{

    Log_ = Log;
    Bot_ = std::make_shared<Bot>(Log_);
//    Search_Window = Window;


    connect(&qnam, &QNetworkAccessManager::authenticationRequired,
            this, &HttpRequest::slotAuthenticationRequired);

#ifndef QT_NO_SSL
    connect(&qnam, &QNetworkAccessManager::sslErrors,
            this, &HttpRequest::sslErrors);
#endif


}



void HttpRequest::startRequest(std::vector<QString> Request)
{

    Request_ = Request;
    Log_->appendText("************************");

    httpRequestAborted = false;

    reply = qnam.get(QNetworkRequest(Request[0]));
    connect(reply, &QNetworkReply::finished, this, &HttpRequest::httpFinished);
    connect(reply, &QIODevice::readyRead, this, &HttpRequest::httpReadyRead);


}



void HttpRequest::cancelDownload()
{

}

void HttpRequest::httpFinished()
{

    if (httpRequestAborted) {
        reply->deleteLater();
        reply = nullptr;
        return;
    }

    if (reply->error()) {
        reply->deleteLater();
        reply = nullptr;
        return;
    }

    const QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    reply->deleteLater();
    reply = nullptr;

    if (!redirectionTarget.isNull()) {
        const QUrl redirectedUrl = QUrl(Request_[0]).resolved(redirectionTarget.toUrl());

        Request_[0] = redirectedUrl.toString();

        startRequest(Request_);
        return;
    }
    else
    {
        emit requestResult(Content_);

        Bot_->searchPrefix(Content_, Request_[1], Request_[2]);
    }

}

void HttpRequest::httpReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    Content_ += reply->readAll();
}

void HttpRequest::enableDownloadButton()
{
}

void HttpRequest::slotAuthenticationRequired(QNetworkReply *, QAuthenticator *authenticator)
{

    (void)authenticator;

    // Did the URL have information? Fill the UI
    // This is only relevant if the URL-supplied credentials were wrong

}

#ifndef QT_NO_SSL
void HttpRequest::sslErrors(QNetworkReply *, const QList<QSslError> &errors)
{
    QString errorString;
    for (const QSslError &error : errors)
    {
        if (!errorString.isEmpty())
            errorString += '\n';
        errorString += error.errorString();
    }

    reply->ignoreSslErrors();

}
#endif
