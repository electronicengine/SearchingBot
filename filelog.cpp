#include <QDir>
#include <iostream>
#include <QStandardPaths>
#include <logview.h>
#include <searchwindow.h>
#include <QMessageBox>
#include "filelog.h"
#include "loging.h"
#include "ui_filelog.h"

FileLog::FileLog(OpsType Ops, MainWindowType Type, QWidget *MainWindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileLog)
{
    ui->setupUi(this);

    if(Ops == save)
        ui->ops_name->setText("Save");
    else if(Ops == open)
        ui->ops_name->setText("Open");

    MainWindow_Type = Type;
    Operation_Type = Ops;
    Main_Window = MainWindow;

    List_Object = std::make_shared<QmlListObject>(ui->quickWidget);

    connect(ui->ok_button, SIGNAL(clicked(bool)), this, SLOT(okButtonClicked()));
    connect(ui->delete_button, SIGNAL(clicked(bool)), this, SLOT(deleteButtonClicked()));

    listFiles();

}



FileLog::~FileLog()
{
    delete ui;
}



void FileLog::okButtonClicked()
{

    QString writable = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QDir dir(writable);
    if (!dir.exists())
    {
        Loging::printAll(Loging::white, "directory doesn't exist!" );
      QDir().mkdir(writable);
    }

    if(Operation_Type == save)
    {
        fileSaveOperation();
    }
    else if(Operation_Type == open)
    {
        fileOpenOperation();
    }

    deleteLater();
}



void FileLog::deleteButtonClicked()
{
    QString writable = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString file_name = List_Object->getCurrentItemText();

    QFile file(writable + "/" + file_name);
    file.remove();

    List_Object->clearList();

    listFiles();

    QMessageBox::information(this, "Delete File", "File is Deleted!");

}



void FileLog::fileOpenOperation()
{

    if(MainWindow_Type == log_view)
    {
        LogView *log_view = dynamic_cast<LogView *>(Main_Window);

        log_view->openFileCallBack(getSelectedFileContent());

    }
    else if(MainWindow_Type == search_window)
    {
        SearchWindow * search_window =  dynamic_cast<SearchWindow *>(Main_Window);

        search_window->searchUrlListFileOpenCallBack(getCategorizedContent());


    }
}



void FileLog::fileSaveOperation()
{

    QString writable = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);


    QFile file(writable + "/" + ui->file_name->text());

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      // We're going to streaming text to the file
      QTextStream stream(&file);

      stream << dynamic_cast<LogView *>(Main_Window)->getAllText();

      file.close();
    }

    QMessageBox::information(this, "File Save", "File Saved");
}



std::vector<QStringList> FileLog::getCategorizedContent()
{
    std::vector<QStringList> categorized_data;

    QString writable = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString file_name = List_Object->getCurrentItemText();

    QFile inputFile(writable + "/" + file_name);
    QString line;
    QStringList temp_list;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {

          temp_list = in.readLine().split("||");

          if(temp_list.size() > (int)categorized_data.size())
          {
              for(int i=0; i<temp_list.size(); i++)
                    categorized_data.push_back(QStringList());
          }

          for(int i=0; i<temp_list.size(); i++)
          {
              if(temp_list.at(i) != "" || temp_list.at(i) != " ")
                categorized_data.at(i).append(temp_list.at(i).simplified());
          }

          temp_list.clear();

       }

       inputFile.close();
    }



    return categorized_data;
}



QString &FileLog::getSelectedFileContent()
{

    QString writable = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QString file_name = List_Object->getCurrentItemText();

    QFile file(writable + "/" + file_name);
    file.open(QIODevice::ReadOnly);

    QTextStream s1(&file);
    File_Content.append(s1.readAll());

    return File_Content;

}



void FileLog::listFiles()
{
    QString writable = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    Loging::printAll(Loging::white, writable.toStdString() );
    QDir directory(writable);
    QStringList file_names = directory.entryList(QStringList() << "*" ,QDir::Files);

    for(int i=0; i<file_names.size(); i++)
        List_Object->addItem(file_names.at(i));
}
