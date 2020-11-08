
#include <QQmlContext>
#include <QtQml/QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlProperty>
#include <QUrl>
#include <QQuickItem>
#include <QMetaObject>
#include "searchwindow.h"
#include "httprequest.h"
#include "ui_searchwindow.h"

SearchWindow::SearchWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);


    List_Object = std::make_shared<QmlListObject>(ui->url_list);
    Log_View = std::make_shared<LogView>();
    Http_Request = std::make_shared<HttpRequest>(Log_View.get());

    connect(ui->look_logs_button, SIGNAL(clicked()), this, SLOT(showLogButtonClicked()));
    connect(ui->url_add_button, SIGNAL(clicked()), this, SLOT(addListButtonClicked()));
    connect(ui->clear_list_button, SIGNAL(clicked()), this, SLOT(clearButtonClicked()));
    connect(ui->start_button, SIGNAL(toggled(bool)), this, SLOT(startButtonClicked()));



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
