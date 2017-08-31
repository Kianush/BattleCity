import QtQuick 1.1
Rectangle {
    property string texture: ""
    property bool active: true
    //color: "#FF000000"
    width: 40
    height: 40
    z: 1

    Image {
        x: 0
        y: 0
        source: parent.texture//"";//Images/external_wall.png"
        visible: parent.active
    }
}
