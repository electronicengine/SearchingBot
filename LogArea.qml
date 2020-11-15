import QtQuick 2.0
import QtQml 2.0
import QtQuick.Controls 2.0
import QtQml.Models 2.1
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.0


Item
{




    Flickable {
        id: flickable
        anchors.fill: parent

        TextArea.flickable: TextArea
        {
            id: textArea
            objectName: "textarea"
            color: "#67cbef"
            width: parent.width
            height: parent.height
            readOnly: true
            persistentSelection: true
            background: Rectangle
          {
              anchors.fill: parent
              color: "#272d2f"
          }

            // Different styles have different padding and background
            // decorations, but since this editor is almost taking up the
            // entire window, we don't need them.
            leftPadding: 6
            rightPadding: 6
            topPadding: 120
            bottomPadding: 0
            selectByMouse: false

            function getAllText() : string
            {
                return textArea.text
            }

        }


        ScrollBar.vertical: ScrollBar {}
    }


    RoundButton {
        id: editButton
        font.family: "fontello"
        text: "Edit" // icon-pencil
        width: 120
        height: 120
        background: Rectangle {
                    radius: 40
                    color: "#67cbef"
                }
        // Don't want to use anchors for the y position, because it will anchor
        // to the footer, leaving a large vertical gap.
        y: parent.height - height - 12
        anchors.right: parent.right
        anchors.margins: 12
        visible: textArea.readOnly
        highlighted: true

        onClicked: {
            textArea.readOnly = false
            textArea.selectByMouse = true
            // Force focus on the text area so the cursor and footer show up.
            textArea.forceActiveFocus()
        }
    }

    ToolButton {
        id: doneEditingButton
        font.family: "fontello"
        text: "ok" // icon-ok
        width: 120
        height: 120
        background: Rectangle {
                    radius: 40
                    color: "#67cbef"
                }
        opacity: !textArea.readOnly ? 1 : 0
        onClicked: {textArea.readOnly = true
            textArea.selectByMouse = false}

    }


}
