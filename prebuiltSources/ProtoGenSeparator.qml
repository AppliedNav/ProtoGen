import QtQuick 2.11
import QtQuick.Controls 2.5

Item {
    id: control
    property bool subsection: false
    property alias label: sepLbl.text
    property alias comment: sepToolTip.text
    readonly property int horizontalMargin: 20
    width: win.width
    height: sepLblFrame.height
    Rectangle {
        id: sepLeft
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: (control.subsection ? control.horizontalMargin : 0)
            right: sepLblFrame.left
        }
        width: parent.width + (control.subsection ? -2*control.horizontalMargin : 0)
        height: control.subsection ? 1 : 2
        color: "grey"
    }
    Rectangle {
        id: sepLblFrame
        color: "transparent"
        anchors.horizontalCenter: parent.horizontalCenter
        border {
            color: sepLeft.color
            width: 1
        }
        height: sepLbl.height + 10
        width: sepLbl.width + 10
        radius: height / 2
        Label {
            id: sepLbl
            anchors {
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            clip: true
            elide: Text.ElideRight
            font.pointSize: control.subsection ? 8 : 10
            ToolTip {
                id: sepToolTip
            }
            MouseArea {
                enabled: "" !== sepToolTip.text
                anchors.fill: parent
                hoverEnabled: true
                onEntered: sepToolTip.visible = true
                onExited: sepToolTip.visible = false
            }
        }
    }
    Rectangle {
        anchors {
            verticalCenter: parent.verticalCenter
            left: sepLblFrame.right
            right: parent.right
            rightMargin: (control.subsection ? control.horizontalMargin : 0)
        }
        width: parent.width + (control.subsection ? -2*control.horizontalMargin : 0)
        height: control.subsection ? 1 : 2
        color: sepLeft.color
    }
}
