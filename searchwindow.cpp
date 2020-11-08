
#include <QQmlContext>
#include <QMessageBox>
#include <QtQml/QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlProperty>
#include <QUrl>
#include <QQuickItem>
#include <QMetaObject>
#include <QDebug>
//#include <QtAndroid>
#include "searchwindow.h"
#include "httprequest.h"
#include "filelog.h"
#include "ui_searchwindow.h"

SearchWindow::SearchWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);

//    auto  result = QtAndroid::checkPermission(QString("android.permission.READ_EXTERNAL_STORAGE"));
//        if(result == QtAndroid::PermissionResult::Denied){
//            QtAndroid::PermissionResultMap resultHash = QtAndroid::requestPermissionsSync(QStringList({"android.permission.READ_EXTERNAL_STORAGE"}));
//            if(resultHash["android.permission.READ_EXTERNAL_STORAGE"] == QtAndroid::PermissionResult::Denied)
//                qDebug() << "permission denied read";

//        }

//    result = QtAndroid::checkPermission(QString("android.permission.WRITE_EXTERNAL_STORAGE"));
//        if(result == QtAndroid::PermissionResult::Denied){
//            QtAndroid::PermissionResultMap resultHash = QtAndroid::requestPermissionsSync(QStringList({"android.permission.WRITE_EXTERNAL_STORAGE"}));
//            if(resultHash["android.permission.WRITE_EXTERNAL_STORAGE"] == QtAndroid::PermissionResult::Denied)
//                qDebug() << "permission denied write";
//        }


    Log_View = new LogView();

    List_Object = std::make_shared<QmlListObject>(ui->url_list);
    Http_Request = std::make_shared<HttpRequest>(Log_View);

    connect(ui->look_logs_button, SIGNAL(clicked()), this, SLOT(showLogButtonClicked()));
    connect(ui->url_add_button, SIGNAL(clicked()), this, SLOT(addListButtonClicked()));
    connect(ui->clear_list_button, SIGNAL(clicked()), this, SLOT(clearButtonClicked()));
    connect(ui->start_button, SIGNAL(toggled(bool)), this, SLOT(startButtonClicked()));
    connect(ui->open_list_button, SIGNAL(clicked()), this, SLOT(openUrlListFileButtonClicked()));


}



SearchWindow::~SearchWindow()
{
    delete ui;
}



void SearchWindow::appendUrlList(const QString &Str)
{

    List_Object->addItem(Str);

}



void SearchWindow::showLogButtonClicked()
{

    if(Log_View != nullptr)
        Log_View->show();
}



void SearchWindow::addListButtonClicked()
{
    const QString &search_url = ui->search_url->text();
    const QString &search_prefix = ui->search_prefix->text();
    const QString &ban_prefix = ui->ban_prefix->text();

    appendUrlList(QString("Search Url: ") + search_url +
                  QString("\nSearch Prefix: ") + search_prefix +
                  QString("\nDelete Prefix: ") + ban_prefix);

    Search_Queue.push(std::vector<QString>({search_url, search_prefix, ban_prefix}));

}



void SearchWindow::clearButtonClicked()
{
    List_Object->clearList();

    for(int i=0; i<(int)Search_Queue.size(); i++)
        Search_Queue.pop();
}



void SearchWindow::startButtonClicked()
{

    Log_View->show();

    for(int i=0; i<(int)Search_Queue.size(); i++)
    {
        Http_Request->startRequest(Search_Queue.front());
        Search_Queue.pop();
    }

}



void SearchWindow::openUrlListFileButtonClicked()
{
    FileLog *file_log = new FileLog(open, search_window, this);

    file_log->show();
}



void SearchWindow::searchUrlListFileOpenCallBack(const QStringList &UrlList)
{
    QString url = ui->search_url->text();
    const QString &search_prefix = ui->search_prefix->text();
    const QString &ban_prefix = ui->ban_prefix->text();
    int prefix_index = url.indexOf('*');

    if(prefix_index < 0)  // no prefix
    {
        for(int i = 0; i < UrlList.size(); i++)
        {
            appendUrlList(QString("Search Url: ") + UrlList.at(i)  +
                          QString("\nSearch Prefix: ") + search_prefix +
                          QString("\nDelete Prefix: ") + ban_prefix);

            Search_Queue.push(std::vector<QString>({UrlList.at(i), search_prefix, ban_prefix}));

        }
    }
    else
    {
        QStringList url_pieces = url.split('*');

        if(url_pieces.size() != 2)
        {
            QMessageBox::information(this, "Error", "Url Prefix must be has one * prefix!");
        }
        else
        {
            url.clear();

            for(int i=0; i<UrlList.size(); i++)
            {
                url = url_pieces.at(0) + UrlList.at(i) + url_pieces.at(1);

                appendUrlList(QString("Search Url: ") + url  +
                              QString("\nSearch Prefix: ") + search_prefix +
                              QString("\nDelete Prefix: ") + ban_prefix);

                Search_Queue.push(std::vector<QString>({UrlList.at(i), search_prefix, ban_prefix}));
            }
        }
    }
}
