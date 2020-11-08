#ifndef FILELOG_H
#define FILELOG_H

#include <QWidget>
#include "qmllistobject.h"

enum OpsType
{
    save,
    open
};

enum MainWindowType
{
    log_view,
    search_window
};


namespace Ui {
class FileLog;
}

class FileLog : public QWidget
{
    Q_OBJECT

public:
    explicit FileLog(OpsType Ops, MainWindowType Type, QWidget *MainWindow, QWidget *parent = nullptr);
    ~FileLog();

private slots:
    void okButtonClicked();
    void deleteButtonClicked();


private:
    Ui::FileLog *ui;
    std::shared_ptr<QmlListObject> List_Object;
    QWidget *Main_Window;
    MainWindowType MainWindow_Type;
    OpsType Operation_Type;
    QString File_Content;

    QString &getSelectedFileContent();
    void listFiles();

};

#endif // FILELOG_H
