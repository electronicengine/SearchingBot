#include <QUrl>
#include <QQmlContext>
#include <QtQml/QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlProperty>
#include <QUrl>
#include <QQuickItem>
#include "logview.h"
#include "ui_logview.h"

LogView::LogView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogView)
{
    ui->setupUi(this);

    ui->quickWidget->setSource(QUrl("qrc:/LogArea.qml"));
}


LogView::~LogView()
{
    delete ui;
}



void LogView::appendText(const QString &Txt)
{

    QObject *rect = ui->quickWidget->rootObject()->findChild<QObject*>("textarea");

    QMetaObject::invokeMethod(rect, "append",
                                  Q_ARG(QString, Txt));
}
