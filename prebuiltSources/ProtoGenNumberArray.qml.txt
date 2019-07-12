import QtQuick 2.9
import QtQuick.Controls 2.3

Row {
    id: control

    property alias val: protoGenNumberArrayList.model
    property int precision: 4

    property alias label: protoGenNumberArrayLabel.text
    property alias units: protoGenNumberArrayUnits.text
    property string comment: ""

    readonly property int fontSize: 10

    width: parent.width
    height: 44
    spacing: 10

    Label {
        id: protoGenNumberArrayLabel
        clip: true
        font.pointSize: control.fontSize
        width: control.width/3-control.spacing
        height: control.height
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        ToolTip {
            text: control.comment
            visible: ("" !== control.comment) ? mouseArea.containsMouse : false
        }
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
        }
    }

    Component {
        id: listDelegate
        Item {
            height: control.height
            width: protoGenNumberArrayValue.width
            TextField {
                id: protoGenNumberArrayValue
                width: 60
                text: control.val[index].toFixed(control.precision)
                validator: DoubleValidator {decimals: control.precision}
                font.pointSize: fontSize
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                onAccepted: {
                    control.val[index] = text
                    text = control.val[index].toFixed(control.precision)
                    parent.parent.synchro = false
                }
                background: Rectangle {
                    height: 24 + 5
                    color: protoGenNumberArrayValue.focus ? "gray" : "transparent"
                    border.color: protoGenNumberArrayValue.focus ? "white" : "gray"
                }
            }
            Label {
                anchors {
                    bottom: parent.bottom
                    bottomMargin: 0
                    horizontalCenter: parent.horizontalCenter
                }
                text: index
            }
        }
    }
    ListView {
        id: protoGenNumberArrayList
        width: control.width/2-control.spacing
        height: control.height
        orientation: ListView.Horizontal
        boundsBehavior: ListView.StopAtBounds
        spacing: 4
        clip: true
        delegate: listDelegate
        ScrollBar.horizontal: ScrollBar {
            policy: ScrollBar.AsNeeded
            snapMode: ScrollBar.SnapAlways
        }
    }

    Label {
        id: protoGenNumberArrayUnits
        clip: true
        font.pointSize: control.fontSize
        width: parent.width/6-parent.spacing
        height: parent.height
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
