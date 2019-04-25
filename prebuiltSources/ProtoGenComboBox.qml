import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

Row {
    id: control

    property alias val: protoGenComboValue.currentIndex
    property var options: ["First", "Second"]

    property alias label: protoGenComboLabel.text
    property string comment: ""

    readonly property int fontSize: 10

    width: parent.width
    height: 24
    spacing: 10

    Label {
        id: protoGenComboLabel
        clip: true
        text: label
        font.pointSize: fontSize
        width: parent.width/3-10
        height: parent.height
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        ToolTip.text: control.comment
        ToolTip.visible: ("" !== control.comment) ? mouseArea.containsMouse : false
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
        }
    }

    ComboBox {
        id: protoGenComboValue
        model: options
        width: parent.width/2
        height: parent.height
        font.pointSize: fontSize
        background.height: parent.height
        popup: Popup {
            y: protoGenComboValue.height - 1
            width: protoGenComboValue.width
            implicitHeight: contentItem.implicitHeight
            padding: 1

            contentItem: ListView {
                clip: true
                implicitHeight: contentHeight
                model: protoGenComboValue.popup.visible ? protoGenComboValue.delegateModel : null
                currentIndex: protoGenComboValue.highlightedIndex
                ScrollIndicator.vertical: ScrollIndicator { }
            }

            background: Rectangle {
                color: Material.background
                border.color: "gray"
                radius: 2
            }
        }
        onCurrentIndexChanged: {
            parent.parent.synchro = false
        }
    }
}
