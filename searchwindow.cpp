
#include <QQmlContext>
#include <QMessageBox>
#include <QtQml/QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlProperty>
#include <QUrl>
#include <QQuickItem>
#include <QMetaObject>
#include <QDebug>
#include <functional>
#include <searchqueueworker.h>
#include <iostream>
//#include <QtAndroid>
#include "searchwindow.h"
#include "searchengine.h"
#include "filelog.h"
#include "searchprocessbox.h"
#include "loging.h"
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

    connect(ui->look_logs_button, SIGNAL(clicked()), this, SLOT(showLogButtonClicked()));
    connect(ui->url_add_button, SIGNAL(clicked()), this, SLOT(addListButtonClicked()));
    connect(ui->clear_list_button, SIGNAL(clicked()), this, SLOT(clearButtonClicked()));
    connect(ui->start_button, SIGNAL(toggled(bool)), this, SLOT(startButtonToggled(bool)));
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

    appendSearchList(search_url, search_prefix, ban_prefix);

}



void SearchWindow::clearButtonClicked()
{
    List_Object->clearList();

    for(int i=0; i<(int)Search_Queue.size(); i++)
        Search_Queue.pop();
}







void SearchWindow::openUrlListFileButtonClicked()
{
    FileLog *file_log = new FileLog(open, search_window, this);

    file_log->show();
}



void SearchWindow::lockInterface(bool Value)
{
    ui->url_add_button->setDisabled(Value);
    ui->look_logs_button->setDisabled(Value);
    ui->clear_list_button->setDisabled(Value);

    ui->start_button->setDisabled(Value);
    ui->open_list_button->setDisabled(Value);
}



void SearchWindow::searchUrlListFileOpenCallBack(const QStringList &UrlList)
{
    const QStringList &url = ui->search_url->text().split(",");
    const QStringList &search_prefix = ui->search_prefix->text().split(",");
    const QStringList &ban_prefix = ui->ban_prefix->text().split(",");
    int prefix_index = url.at(0).indexOf('*');

    if(prefix_index < 0)  // no prefix
    {
        for(int i = 0; i < UrlList.size(); i++)
        {
//            appendUrlList(QString("Search Url: ") + ui->search_url->text()  +
//                          QString("\nSearch Prefix: ") + ui->search_prefix->text() +
//                          QString("\nDelete Prefix: ") + ui->ban_prefix->text());

//            File_Input_List.push_back(UrlList.at(i));

//            Search_Queue.push(std::vector<QStringList>({UrlList, search_prefix, ban_prefix}));

        }
    }
    else
    {
//        QStringList url_pieces = url.split('*');

//        if(url_pieces.size() != 2)
//        {
//            QMessageBox::information(this, "Error", "Url Prefix must be has one * prefix!");
//        }
//        else
//        {
//            url.clear();

//            for(int i=0; i<UrlList.size(); i++)
//            {
//                url = url_pieces.at(0) + UrlList.at(i) + url_pieces.at(1);

//                appendUrlList(QString("Search Url: ") + url  +
//                              QString("\nSearch Prefix: ") + search_prefix +
//                              QString("\nDelete Prefix: ") + ban_prefix);

//                Search_Queue.push(std::vector<QString>({UrlList.at(i), search_prefix, ban_prefix}));
//                File_Input_List.push_back(UrlList.at(i));

//            }
//        }
    }
}



void SearchWindow::startButtonToggled(bool Value)
{

    if(Value == true)
    {
        Thread_Pool.setMaxThreadCount(ui->thread_number->value());

        Queue_Size = Search_Queue.size();


        Progress_Bar = new SearchProcessBox;
        Progress_Bar->show();

        for(int i=0; i<(int)Queue_Size; i++)
        {

            std::vector<QStringList> &current_search =
                    Search_Queue.front();
            SearchQueueWorker *worker = new SearchQueueWorker(i, current_search, this);
            worker->setAutoDelete(true);

            Thread_Pool.start(worker);
            Search_Queue.pop();

        }

        List_Object->clearList();

        Log_View->show();
    }

}



void SearchWindow::searchResultCallBackFunction(const std::vector<QStringList> &ResultList, int QueueId)
{

    std::unique_lock<std::mutex> ul(Mutex_);
    QString plain_text;

    static int complated_queue_counter = 0;
    complated_queue_counter++;

    Progress_Bar->show();

    Progress_Bar->setPersentage((double)complated_queue_counter/Queue_Size);

    Log_View->appendText("\n******************************************************************************************************");
    Log_View->appendText(QString::number(QueueId).rightJustified(3, '0') + "***********************************Search Result Seperator****************************************");
    Log_View->appendText("******************************************************************************************************\n");

    if(Queue_Size == (int)File_Input_List.size())
        Log_View->appendText("Query Prefix: " + File_Input_List.at(QueueId));

    for(int k = 0; k < (int)ResultList[0].size(); k++)
    {
        for(int i = 0; i< (int) ResultList.size(); i++)
        {
            if(ResultList.at(i).size() >= k)
                plain_text += ResultList.at(i).at(k) + "\t||\t";
        }
        plain_text += "\n";
    }

    Log_View->appendText(plain_text);

    QThread::sleep(1);

    if((double)complated_queue_counter/Queue_Size == 1)
    {
        complated_queue_counter = 0;
        ui->start_button->setChecked(false);
        Queue_Size = 0;

        delete Progress_Bar;
    }

}




void SearchWindow::appendSearchList(const QString &UrlList, const QString &PrefixList, const QString &BanList)
{

    const QStringList &search_url = UrlList.split(",");
    const QStringList &search_prefix = PrefixList.split(",");
    const QStringList &ban_prefix = BanList.split(",");

    QStringList simplified_search_url;
    QStringList simplified_search_prefix;
    QStringList simplified_ban_prefix;

    appendUrlList(QString("Search Url: ") + UrlList +
                  QString("\nSearch Prefix: ") + PrefixList +
                  QString("\nDelete Prefix: ") + BanList);

    foreach (QString var, search_url)
    {
        Loging::printAll(Loging::cyan, "search_url:", var.toStdString());
        if(var.simplified() != "")
            simplified_search_url.append(var.simplified());
    }
    foreach (QString var, search_prefix)
    {
        Loging::printAll(Loging::cyan, "search_prefix:", var.toStdString());

        if(var.simplified() != "")
            simplified_search_prefix.append(var.simplified());
    }
    foreach (QString var, ban_prefix)
    {
        Loging::printAll(Loging::cyan, "ban_prefix: ", var.toStdString());

        if(var.simplified() != "")
            simplified_ban_prefix.append(var.simplified());
    }

    Search_Queue.push(std::vector<QStringList>({simplified_search_url,
                                                simplified_search_prefix, simplified_ban_prefix}));

}
