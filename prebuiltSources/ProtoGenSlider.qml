import QtQuick 2.9
import QtQuick.Controls 2.3

Row {
    id: control

    property double val: 0
    property double minval: 0
    property double maxval: 1
    property double step: 0.1
    property int precision: 2

    property alias label: protoGenSliderLabel.text
    property alias units: protoGenSliderUnits.text
    property string comment: ""

    readonly property int fontSize: 10

    width: parent.width
    height: 24
    spacing: 10

    Label {
        id: protoGenSliderLabel
        font.pointSize: control.fontSize
        width: parent.width/3-4
        height: parent.height
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

    Slider {
        id: protoGenSliderValue
        from: minval
        to: maxval
        stepSize: step
        snapMode: Slider.SnapAlways
        value: val
        width: parent.width/2-4
        height: parent.height
        ToolTip {
            parent: protoGenSliderValue.handle
            visible: protoGenSliderValue.pressed
            text: protoGenSliderValue.valueAt(protoGenSliderValue.position).toFixed(control.precision)
        }
        onValueChanged: {
            control.val = protoGenSliderValue.valueAt(protoGenSliderValue.position).toFixed(control.precision)
            parent.parent.synchro = false
        }
    }

    Label {
        id: protoGenSliderUnits
        font.pointSize: control.fontSize
        width: parent.width/6-4
        height: parent.height
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
