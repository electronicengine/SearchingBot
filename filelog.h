#ifndef FILELOG_H
#define FILELOG_H

#include <QWidget>
#include <functional>
#include <memory>
#include "qmllistobject.h"

enum OpsType
{
    save,
    open,
    data_base,
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
    void fileOpenOperation();
    void fileSaveOperation();
    void savetoDataBaseOperation();
    std::vector<QStringList> getCategorizedContent();


private:
    Ui::FileLog *ui;
    std::shared_ptr<QmlListObject> List_Object;
    QWidget *Main_Window;
    MainWindowType MainWindow_Type;
    OpsType Operation_Type;
    QString File_Content;

    QString &getSelectedFileContent();
    void listFiles();
    void createTable();
    void insertValues(int Id, const QString &Header, const QStringList &Values);

};

#endif // FILELOG_H
