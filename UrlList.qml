import QtQuick 2.0
import QtQml 2.0
import QtQuick.Controls 2.0
import QtQml.Models 2.1

Item
{


    Flickable
    {
        id: flickable
        anchors.fill: parent
        contentWidth: 2000


        Rectangle
        {
            anchors.fill: parent

            color: "#272d2f"
        }

        ListView
        {

            id: myListView
            width: parent.width
            height: parent.height
            model:myModel

            focus: true
            highlight: Rectangle { color: "blue"; radius: 10 }

            function myQmlFunction(msg) {
                console.log("Got message:", msg)
                return "some return value"
            }

            delegate: Component
            {

                Item
                {
                    property variant itemData: model.modelData
                    width: column.width
                    height: column.height


                    Column
                    {
                        id:column
                        Text
                        {
                            text: name
                            wrapMode: Text.WordWrap
                            color: "#67cbef"
                        }

                    }

                    MouseArea
                    {
                        id: itemMouseArea
                        anchors.fill: parent
                        onClicked:
                        {
                            myListView.currentIndex = index

                        }
                    }

                }

            }

            onCurrentItemChanged: searchwindow.currentItemIdexChanged(myListView.currentIndex)
        }


    }
}
