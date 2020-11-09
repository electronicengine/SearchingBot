#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>
#include <QThreadPool>
#include <memory>
#include <vector>
#include <queue>
#include "logview.h"
#include "qmllistobject.h"
#include "httprequest.h"
#include "searchprocessbox.h"


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
    void searchUrlListFileOpenCallBack(const QStringList &UrlList);
    void searchResultCallBackFunction(const QStringList &ResultList);

private slots:
    void showLogButtonClicked();
    void addListButtonClicked();
    void clearButtonClicked();
    void startButtonToggled(bool Value);
    void openUrlListFileButtonClicked();

private:
    Ui::SearchWindow *ui;

    LogView *Log_View;
    std::shared_ptr<QmlListObject> List_Object;
    SearchProcessBox *Progress_Bar;
    std::queue<std::vector<QString>> Search_Queue;
    HttpRequest Http_Request;
    QThreadPool Thread_Pool;
    std::mutex Mutex_;
    void lockInterface(bool Value);
    int Queue_Size;

};

#endif // SEARCHWINDOW_H
