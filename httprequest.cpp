/****************************************************************************

****************************************************************************/
#include <QtNetwork>
#include <QUrl>

#include "httprequest.h"

#if QT_CONFIG(ssl)
const char defaultUrl[] = "https://www.qt.io/";
#else
const char defaultUrl[] = "http://www.qt.io/";
#endif
const char defaultFileName[] = "index.html";



HttpRequest::HttpRequest(QObject *parent)
    : QObject(parent)
    , reply(nullptr)
    , httpRequestAborted(false)
    , httpRequestFinished(false)
{


    connect(&qnam, &QNetworkAccessManager::authenticationRequired,
            this, &HttpRequest::slotAuthenticationRequired);

#ifndef QT_NO_SSL
    connect(&qnam, &QNetworkAccessManager::sslErrors,
            this, &HttpRequest::sslErrors);
#endif


}



void HttpRequest::startRequest(const QUrl &requestedUrl)
{

    url = requestedUrl;
    httpRequestAborted = false;

    reply = qnam.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &HttpRequest::httpFinished);
    connect(reply, &QIODevice::readyRead, this, &HttpRequest::httpReadyRead);


}



void HttpRequest::makeRequest(const QUrl &Address)
{
    startRequest(Address);
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
        const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());

        startRequest(redirectedUrl);
        return;
    }
    else
    {
        emit requestResult(Content_);

        qDebug() << "************************";

    //    QString result = reply->readAll();
        QString result = "*9134*129ı4kpğiewr<a href=\"/diseases-conditions/acanthosis-nigricans/symptoms-causes/syc-20368983\">Acanthosis nigricans</a>WFWEWFWEF23";

        QString beginning = "<a href=";
        QString ending = "</a>";
        int begin = 0;
        int end = 0;
        do
        {

            begin = result.indexOf(beginning);
            if(begin >= 0)
            {
                end = result.indexOf(ending);

                if(end >= 0)
                {
                    QString sub_str = result.left(end);
                    QString extracted = sub_str.mid(begin + beginning.size());

                    qDebug() << extracted << "\n\n";

                }
                else
                    qDebug() << "Cannot find last";
            }
            else
            {
                qDebug() << "Cannot find anymore";
                break;
            }

        }while(begin < 0);
    }

}

void HttpRequest::httpReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    Content_ = reply->readAll();


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
