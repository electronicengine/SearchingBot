#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QString>
#include <QApplication>
#include <QSslSocket>
#include "loging.h"
#include "searchwindow.h"
#include "botunittest.h"




int main(int argc, char *argv[])
{

    BotUnitTest test;

    QApplication a(argc, argv);

    Loging::enableLogs();

    SearchWindow *search_window = new SearchWindow;

    search_window->show();

    return a.exec();
}
