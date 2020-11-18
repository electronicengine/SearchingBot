#include <QDir>
#include <iostream>
#include <QStandardPaths>
#include <logview.h>
#include <searchwindow.h>
#include <QMessageBox>
#include <QtSql>
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
    else if(Ops == data_base)
        ui->ops_name->setText("Pack");

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
    else if(Operation_Type == data_base)
    {
        savetoDataBaseOperation();
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


    QFile file(writable + "/" + ui->file_name->text() + ".log");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      // We're going to streaming text to the file
      QTextStream stream(&file);

      stream << dynamic_cast<LogView *>(Main_Window)->getAllText();

      file.close();
    }

    QMessageBox::information(this, "File Save", "File Saved");
}



void FileLog::createTable(int ColumnSize)
{

    QString query_str;
    QSqlQuery query;

    query_str = "CREATE TABLE a_table (ID integer";

    for(int i=0; i<ColumnSize; i++)
    {
        query_str += QString(", Column");
        query_str += QString::number(i) + " VARCHAR(200)";
    }

    query_str += ");";
    Loging::printAll(Loging::yellow, "query str: ", query_str.toStdString());

    query.exec(query_str);
}



void FileLog::insertValues(int Id, const QString &Header, const QStringList &Values)
{
    QString query_str;
    QSqlQuery query;

    query_str = "INSERT INTO a_table (ID";

    for(int i=0; i<Values.size(); i++)
    {
        query_str += ",";
        query_str += "Column";
        query_str += QString::number(i);
    }

    query_str += ") ";
    query_str += "VALUES (" + QString::number(Id) + ",\"" + Header + "\"";

    for(int i=0; i<Values.size() - 1; i++)
    {
        query_str += ",\"";
        query_str += Values.at(i).simplified();
        query_str += "\"";
    }

    query_str += "); ";

    Loging::printAll(Loging::yellow, "query str: ", query_str.toStdString());

    query.exec(query_str);
}



void FileLog::savetoDataBaseOperation()
{
    QString writable = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setConnectOptions();

    db.setDatabaseName(writable + "/" + ui->file_name->text() + ".db");

    if(db.open())
    {
        int line_counter = 0;
        bool data_base_created = false;
        QSqlQuery query;
        QString query_str;
        QString text = dynamic_cast<LogView *>(Main_Window)->getAllText();
        QTextStream stream(&text);
        QString line;
        QString header_column;

        while (stream.readLineInto(&line))
        {
            if(data_base_created == true)
            {
                if(line.indexOf("====>") < 0)
                {
                    QStringList colums = line.split("||",  Qt::SkipEmptyParts);

                    insertValues(line_counter, header_column, colums);
                }
                else
                {
                    header_column = line.mid(5);
                }
            }
            else if(data_base_created == false)
            {
                if(line.indexOf("====>") < 0)
                {

                    QStringList columns = line.split("||", Qt::SkipEmptyParts);

                    createTable(columns.size());

                    insertValues(line_counter, header_column, columns);

                   data_base_created = true;

                }
                else
                {
                    header_column = line.mid(5);
                }
            }

            line_counter++;
        }

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

           line = in.readLine();
           if(line.indexOf("====>") < 0)
           {
               temp_list = line.split("||");

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




