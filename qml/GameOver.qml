import QtQuick 1.1
//Item {
//    //property bool active: true
//    id: banner
//    width: 618;
//    height: 618;

    //color: "black"
    Item {
        id: gameover_element
        property string result: ""
        property int hi_scope: 0
        property int scope: 0
        property int simple_aliens_killed : 0
        property int speed_aliens_killed: 0
        width: 618;
        height: 618;
        //property bool visible: true
    //}
    Text {
        x: 0
        y: 0
        height: 80
        font.family: "Helvetica"
        font.pointSize: 24
        color: "yellow"
        visible: true
        //anchors: center
        anchors.horizontalCenter: parent.horizontalCenter
        text: gameover_element.result + "<br>" +
              "hi-scope:" + gameover_element.hi_scope + "<br>" +
              "your scope:" + gameover_element.scope +"<br>"+
              "simple panzer killed:" + gameover_element.simple_aliens_killed + "<br>"+
              "speed panzer killed:" + gameover_element.speed_aliens_killed;
    }
    }
// }
