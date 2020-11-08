#ifndef QMLLISTITEM_H
#define QMLLISTITEM_H

#include <QObject>
#include "qmllistitem.h"

class QmlListItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)


public:
    QmlListItem(QObject *parent=0);
    QmlListItem(const QString &name, const QString &color, QObject *parent=0);

    QString name() const;
    void setName(const QString &name);

    QString color() const;
    void setColor(const QString &color);

signals:
    void nameChanged();
    void colorChanged();

private:
    QString m_name;
    QString m_color;
};

#endif // QMLLISTITEM_H
