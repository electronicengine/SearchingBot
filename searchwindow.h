#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>
#include <memory>
#include <vector>
#include <queue>
#include "logview.h"
#include "qmllistobject.h"
#include "httprequest.h"


namespace Ui {
class SearchWindow;
}

class SearchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = nullptr);
    ~SearchWindow();

    void appendUrlList(const QString &Str);

private slots:
    void showLogButtonClicked();
    void addListButtonClicked();
    void clearButtonClicked();
    void startButtonClicked();

private:
    Ui::SearchWindow *ui;

    std::shared_ptr<LogView> Log_View;
    std::shared_ptr<QmlListObject> List_Object;
    std::shared_ptr<HttpRequest> Http_Request;

    std::queue<std::vector<QString>> Search_Queue;

};

#endif // SEARCHWINDOW_H
