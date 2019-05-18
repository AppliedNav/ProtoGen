import QtQuick 2.9
import QtQuick.Controls 2.3

Column {
    property bool synchro: true
    spacing: 10
    Binding {
        target: header
        property: "inSync"
        value: synchro
    }
}
