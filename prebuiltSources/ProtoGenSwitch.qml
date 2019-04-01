import QtQuick 2.9
import QtQuick.Controls 2.3

Row {
    id: control

    property bool val: false

    property alias label: protoGenSwitchLabel.text
    property string comment: ""

    readonly property int fontSize: 10

    width: parent.width
    height: 24
    spacing: 4

    Label {
        id: protoGenSwitchLabel
        font.pointSize: control.fontSize
        width: parent.width/3-4
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

    Label {
        text: "OFF"
        font.pointSize: control.fontSize
        width: parent.width/6-4
        height: parent.height
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
    }

    Switch {
        id: valswitch
        checked: control.val
        width: parent.width/6-4
        height: parent.height
        onClicked: {
            parent.parent.synchro = false
            console.log("ProtoGenSwitch: value changed")
        }
    }

    Label {
        text: "ON"
        font.pointSize: control.fontSize
        width: parent.width/6-4
        height: parent.height
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
    }
}
