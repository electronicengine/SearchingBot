#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QString>
#include <QApplication>
#include "searchwindow.h"





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SearchWindow *search_window = new SearchWindow;

    search_window->show();



    return a.exec();
}
