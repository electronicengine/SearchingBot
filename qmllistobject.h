#ifndef QMLLISTOBJECT_H
#define QMLLISTOBJECT_H

#include <QObject>
#include <QQuickWidget>
#include <qmllistitem.h>
#include <QQuickWidget>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickView>
#include <QObject>
#include <QVariant>


class QmlListObject : public QObject
{

    Q_OBJECT

    QQuickWidget *Widget_;

    QList<QObject *> Item_List;
    int Current_Index;

public:

    QmlListObject(QQuickWidget *Widget, QObject *parent = nullptr)
        : QObject(parent)
    {
        Widget->rootContext()->setContextProperty("searchwindow", this);
        Widget->rootContext()->setContextProperty("myModel", QVariant::fromValue(Item_List));
        Widget->setSource(QUrl("qrc:UrlList.qml"));

        Widget_ = Widget;
    }




    Q_INVOKABLE void currentItemIdexChanged(int Index);

    void addItem(const QString &ItemStr);
    void clearList();
    QString getCurrentItemText();
    QString getItem(int Index);
    void eraseItem(int Index);
    int getSize();
};

#endif // QMLLISTOBJECT_H
