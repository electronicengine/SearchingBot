/****************************************************************************

****************************************************************************/

#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

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

#define FILE_SEARCH_KEYWORD     "file://"
#define HTTP_SEARCH_KEYWORD     "http://"
#define HTTPS_SEARCH_KEYWORD    "https://"
#define EXTERNAL_LOC_KEYWORD    "external"


class SearchEngine
{
//    Q_OBJECT

public:
    SearchEngine();

    void makeHttpSearch(std::vector<QStringList> Request, std::vector<QStringList> &ResultList);
    void makeFileSearch(std::vector<QStringList> Request, std::vector<QStringList> &ResultList);
    void searchRequest(std::vector<QStringList> Request, std::vector<QStringList> &ResultList);

private:



};

#endif
