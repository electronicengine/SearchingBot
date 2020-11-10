#include "qmllistobject.h"





void QmlListObject::currentItemIdexChanged(int Index)
{
    Current_Index = Index;
    qDebug() << Index;
}



void QmlListObject::addItem(const QString &ItemStr)
{

    Item_List.append(new QmlListItem(ItemStr, "black"));
    Widget_->rootContext()->setContextProperty("myModel", QVariant::fromValue(Item_List));

}



void QmlListObject::clearList()
{
    Item_List.clear();
    Widget_->rootContext()->setContextProperty("myModel", QVariant::fromValue(Item_List));

}



QString QmlListObject::getCurrentItemText()
{
    QmlListItem *item = dynamic_cast<QmlListItem*>(Item_List[Current_Index]);

    return item->name();
}



QString QmlListObject::getItem(int Index)
{
    QmlListItem *item = dynamic_cast<QmlListItem*>(Item_List[Index]);
    return item->name();

}



void QmlListObject::eraseItem(int Index)
{
   Item_List.erase(Item_List.begin() + Index);
   Widget_->rootContext()->setContextProperty("myModel", QVariant::fromValue(Item_List));
}



int QmlListObject::getSize()
{
    return Item_List.size();
}
