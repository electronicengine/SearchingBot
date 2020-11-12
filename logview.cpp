#include <QUrl>
#include <QQmlContext>
#include <QtQml/QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlProperty>
#include <QUrl>
#include <QQuickItem>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include "filelog.h"

#include "logview.h"
#include "ui_logview.h"



LogView::LogView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogView)
{
    ui->setupUi(this);

    ui->quickWidget->setSource(QUrl("qrc:/LogArea.qml"));

    connect(ui->clear_button, SIGNAL(clicked(bool)), this, SLOT(clearButtonClicked()));
    connect(ui->save_button, SIGNAL(clicked()), this, SLOT(saveButtonClicked()));
    connect(ui->open_button, SIGNAL(clicked()), this, SLOT(openButtonClicked()));
//    connect(this, SIGNAL(appendTextQueue(QString)), ui->plainTextEdit, SLOT(appendPlainText(QString)), Qt::QueuedConnection);

}


LogView::~LogView()
{
    delete ui;
}



void LogView::appendText(const QString &Txt)
{

//    emit appendTextQueue(Txt);

    QObject *rect = ui->quickWidget->rootObject()->findChild<QObject*>("textarea");

    QMetaObject::invokeMethod(rect, "append",
                              Q_ARG(QString, Txt));
}



QString LogView::getAllText()
{
    QString returnedValue;

    QObject *rect = ui->quickWidget->rootObject()->findChild<QObject*>("textarea");

    QMetaObject::invokeMethod(rect, "getAllText",
            Q_RETURN_ARG(QString, returnedValue));

//    returnedValue = ui->plainTextEdit->toPlainText();

    return returnedValue;
}



void LogView::openFileCallBack(const QString &Content)
{
    clearText();

    appendText(Content);

    QMessageBox::information(this, "File Open", "File Opened");
}



void LogView::clearText()
{
    QObject *rect = ui->quickWidget->rootObject()->findChild<QObject*>("textarea");

    QMetaObject::invokeMethod(rect, "clear");

//    ui->plainTextEdit->clear();
}




void LogView::saveButtonClicked()
{
    FileLog *file_log = new FileLog(save, log_view, this);

    file_log->show();
}



void LogView::openButtonClicked()
{
    FileLog *file_log = new FileLog(open, log_view, this);

    file_log->show();

}



void LogView::clearButtonClicked()
{
    clearText();
}
