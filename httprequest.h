/****************************************************************************

****************************************************************************/

#ifndef HTTPWINDOW_H
#define HTTPWINDOW_H

#include <QNetworkAccessManager>
#include <QUrl>
#include <condition_variable>
#include <QWaitCondition>
#include <QSemaphore>
#include <memory>
#include <mutex>

class HttpWindow;
class QSslError;
class QAuthenticator;
class QNetworkReply;


class HttpRequest : public QObject
{
    Q_OBJECT

public:
    explicit HttpRequest(QObject *parent = nullptr);


    void makeRequest(const QUrl &Address);

    void startRequest(const QUrl &requestedUrl);

private slots:
    void cancelDownload();
    void httpFinished();
    void httpReadyRead();
    void enableDownloadButton();
    void slotAuthenticationRequired(QNetworkReply *, QAuthenticator *authenticator);
#ifndef QT_NO_SSL
    void sslErrors(QNetworkReply *, const QList<QSslError> &errors);
#endif

signals:
    void requestResult(const QString &Content);

private:

    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    bool httpRequestAborted;
    bool httpRequestFinished;
    QString Content_;
    QSemaphore Sem_;

};

#endif
