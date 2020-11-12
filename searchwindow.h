#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>
#include <QThreadPool>
#include <memory>
#include <vector>
#include <queue>
#include "logview.h"
#include "qmllistobject.h"
#include "searchengine.h"
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
    void searchUrlListFileOpenCallBack(const std::vector<QStringList> &FileList);
    void searchResultCallBackFunction(const std::vector<QStringList> &ResultList, int QueueId);
    void appendSearchList(const QString &UrlList, const QString &PrefixList, const QString &BanList);

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
    std::queue<std::vector<QStringList>> Search_Queue;
    std::vector<QString> File_Input_List;
    QThreadPool Thread_Pool;
    std::mutex Mutex_;
    void lockInterface(bool Value);
    int Queue_Size;

};

#endif // SEARCHWINDOW_H
