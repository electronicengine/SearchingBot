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

            TextArea.flickable: TextArea
            {
                id:rt
                background: Rectangle
                {
                    anchors.fill: parent
                    color: "#272d2f"
                }

                objectName: "textarea"
                color: "#67cbef"
                width: parent.width
                height: parent.height
                readOnly: false


                function getAllText() : string
                {
                    return rt.text
                }
            }

            ScrollBar.vertical: ScrollBar { }

    }


}
