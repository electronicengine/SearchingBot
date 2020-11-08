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
    void searchUrlListFileOpenCallBack(const QStringList &UrlList);

private slots:
    void showLogButtonClicked();
    void addListButtonClicked();
    void clearButtonClicked();
    void startButtonClicked();
    void openUrlListFileButtonClicked();

private:
    Ui::SearchWindow *ui;

    LogView *Log_View;
    std::shared_ptr<QmlListObject> List_Object;

    std::queue<std::vector<QString>> Search_Queue;


    void lockInterface(bool Value);


};

#endif // SEARCHWINDOW_H
