#include <QDebug>
#include "qmllistitem.h"

QmlListItem::QmlListItem(QObject *parent)
    : QObject(parent)
{
}

QmlListItem::QmlListItem(const QString &name, const QString &color, QObject *parent)
    : QObject(parent), m_name(name), m_color(color)
{
}

QString QmlListItem::name() const
{
    return m_name;
}

void QmlListItem::setName(const QString &name)
{
    if (name != m_name) {
        m_name = name;
        emit nameChanged();
    }
}

QString QmlListItem::color() const
{
    return m_color;
}

void QmlListItem::setColor(const QString &color)
{
    if (color != m_color) {
        m_color = color;
        emit colorChanged();
    }
}
