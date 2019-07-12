import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.2

Grid {
    id: control

    property bool inSync: true
    readonly property int buttonWidth: 100
    readonly property int buttonHeight: 40
    readonly property int fontSize: 10

    columns: 3
    spacing: 4
    height: buttonHeight*2 + spacing*3
    width: parent.width

    Rectangle {
        width: parent.width/3-parent.spacing
        height: buttonHeight
        color: "transparent"
    }

    FileDialog {
        id: openFileDialog
        visible: false
        title: qsTr("Open an XML file")
        folder: shortcuts.home
        selectExisting: true
        selectFolder: false
        selectMultiple: false
        nameFilters: [ "XML files (*.xml)", "All files (*)" ]
        onAccepted: {
            controller.openFile(openFileDialog.fileUrl)
            openFileDialog.visible = false
        }
        onRejected: openFileDialog.visible = false
    }
    Button {
        id: btnOpen
        text: "Open..."
        font.pointSize: fontSize
        implicitWidth: parent.width/3-parent.spacing
        implicitHeight: buttonHeight
        onClicked: openFileDialog.visible = true
    }

    FileDialog {
        id: saveFileDialog
        visible: false
        title: qsTr("Save to XML file")
        folder: shortcuts.home
        selectExisting: false
        selectFolder: false
        selectMultiple: false
        nameFilters: [ "XML files (*.xml)", "All files (*)" ]
        onAccepted: {
            controller.saveFile(saveFileDialog.fileUrl)
            saveFileDialog.visible = false
        }
        onRejected: saveFileDialog.visible = false
    }
    Button {
        id: btnSave
        text: "Save..."
        font.pointSize: fontSize
        implicitWidth: parent.width/3-parent.spacing
        implicitHeight: buttonHeight

        onClicked: saveFileDialog.visible = true
    }

    Rectangle {
        width: parent.width/3-parent.spacing
        height: buttonHeight
        color: "transparent"

        Rectangle {
            anchors.centerIn: parent
            width: parent.width*0.75
            height: parent.height*0.75
            color: control.inSync ? "green" : "red"
            radius: 4

            Label {
                id: syncIndicator
                text: "IN SYNC"
                color:control.inSync ? "white" : "black"
                font.pointSize: fontSize
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.centerIn: parent
                width: parent.width*0.8
                height: parent.height*0.8
            }
        }
    }

    Button {
        id: btnRequest
        text: "Request"
        font.pointSize: fontSize
        implicitWidth: parent.width/3-parent.spacing
        implicitHeight: buttonHeight

        onClicked: {
            control.inSync = false
            controller.requestData(categoryView.currentIndex)
        }
    }

    Button {
        id: btnSend
        text: "Send"
        font.pointSize: fontSize
        implicitWidth: parent.width/3-parent.spacing
        implicitHeight: buttonHeight

        onClicked: {
            control.inSync = false
            controller.sendData(categoryView.currentIndex)
        }
    }
}

