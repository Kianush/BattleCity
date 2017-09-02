import QtQuick 1.1
//Rectangle {
//    property string texture: ""
//    property bool active: true
//    color: "#FF000000"
//    width: 40
//    height: 40
//    z: 1

    Image {

        property string texture: ""
        property bool active: true
        //color: "#FF000000"
        width: 40
        height: 40
        z: 1

        x: 0
        y: 0
        source: texture//"";//Images/external_wall.png"
        visible: active
    }
//}
