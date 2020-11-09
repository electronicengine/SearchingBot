/****************************************************************************

****************************************************************************/

#ifndef HTTPWINDOW_H
#define HTTPWINDOW_H

#include <QSslSocket>
#include <QNetworkAccessManager>
#include <QUrl>
#include <condition_variable>
#include <QWaitCondition>
#include <QSemaphore>
#include <memory>
#include <mutex>
#include <bot.h>

class HttpWindow;
class QSslError;
class QAuthenticator;
class QNetworkReply;
class LogView;
class SearchWindow;




class HttpRequest
{
//    Q_OBJECT

public:
    HttpRequest();

    void makeRequest(std::vector<QString> Request, QStringList &ResultList);
//private slots:
//    void cancelDownload();
//    void httpFinished();
//    void httpReadyRead();
//    void enableDownloadButton();
//    void slotAuthenticationRequired(QNetworkReply *, QAuthenticator *authenticator);
//#ifndef QT_NO_SSL
//    void sslErrors(QNetworkReply *, const QList<QSslError> &errors);
//#endif

//signals:
//    void requestResult(const QString &Content);

private:

    std::vector<QString> Request_;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    bool httpRequestAborted;
    bool httpRequestFinished;

};

#endif
