#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QString>
#include <QApplication>
#include <QSslSocket>
#include <QSplashScreen>
#include "loging.h"
#include "searchwindow.h"
#include "botunittest.h"




int main(int argc, char *argv[])
{

    BotUnitTest test;

    QApplication a(argc, argv);

    QPixmap pixmap(":/images/cover-h480.png");
    QSplashScreen splash(pixmap);
    splash.show();

    QCoreApplication::processEvents();
    Loging::enableLogs();


    SearchWindow *search_window = new SearchWindow;

    search_window->show();
    splash.finish(search_window);

    return a.exec();
}
