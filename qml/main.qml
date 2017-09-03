import QtQuick 1.0

Rectangle {
    id: canvas
    color: "black"
    width: 980
    height: 618
    anchors.fill: parent
    focus: true
    //Button
    Rectangle {
        //Name of button
        id: button_new_game
        objectName: "object_new_game_button"
        //Dimensions of button
        width: 100
        height: 30

        //right low corner
        x: parent.width - button_new_game.width - 10;
        y: parent.height - button_new_game.height - 10;



        //Цвет кнопки
        color: "green"

        //Текст кнопки
        Text {
            id: buttonLabel
            text: "new game"
            anchors.centerIn: parent;
        }

        //Действие мыши
        MouseArea {
            anchors.fill: parent
            id: mouseArea
            onClicked: window.NewGameButtonQmlClick()
        }
    }

//    Image {
//    x: 0
//    y: 0
        Component.onCompleted: {
                    var component = Qt.createComponent("GameCell.qml");
                    var compName;
                    var sprite;

                    for (var column = 0; column < 15; column++) {
                        for (var row = 0; row < 15; row++) {
                            //if ((column == 0 || column == 14) || (row == 0 || row == 14)) {
                                compName = "c"+column+"r"+row

                                sprite = component.createObject(canvas);
                                if (sprite == null) {
                                    // Error Handling
                                    //console.log("Error creating object");
                                }
                                else {
                                    sprite.x = 0;//column*40;
                                    sprite.y = 0;//row*40;
                                    sprite.active = false;
                                    sprite.objectName = compName;
                                }
                            //}
                        }
                    }
                    //for(var prize_count = 0; prize_count < 10; prize_count++) {
                        compName = "prize";// + prize_count;
                        sprite = component.createObject(canvas);
                        if (sprite == null) {
                            // Error Handling
                            //console.log("Error creating object");
                        }
                        else {
                            sprite.x = -40;//column*40;
                            sprite.y = -40;//row*40;
                            sprite.active = false;
                            sprite.objectName = compName;
                        }
                    //}

                    compName = "our_panzer"
                    sprite = component.createObject(canvas);
                    if (sprite == null) {
                        // Error Handling
                        //console.log("Error creating object");
                    }
                    else {
                        sprite.x = -40;//column*40;
                        sprite.y = -40;//row*40;
                        //sprite.z = 2;
                        sprite.active = false;
                        sprite.objectName = compName;
                    }
                    compName = "our_flag"
                    sprite = component.createObject(canvas);
                    if (sprite == null) {
                        // Error Handling
                        //console.log("Error creating object");
                    }
                    else {
                        sprite.x = -40;//column*40;
                        sprite.y = -40;//row*40;
                        sprite.active = false;
                        sprite.objectName = compName;
                    }
                    for(var bullet_count = 0; bullet_count < 256; bullet_count++) {
                        compName = "bullet_" + bullet_count;
                        sprite = component.createObject(canvas);
                        if (sprite == null) {
                            // Error Handling
                            //console.log("Error creating object");
                        }
                        else {
                            sprite.x = -40;//column*40;
                            sprite.y = -40;//row*40;
                            sprite.width = 7;
                            sprite.height = 7;
                            sprite.active = false;
                            sprite.objectName = compName;
                        }
                    }
                    for(var bullet_explosion_count = 0; bullet_explosion_count < 256; bullet_explosion_count++) {
                        compName = "bullet_explosion_" + bullet_explosion_count;
                        sprite = component.createObject(canvas);
                        if (sprite == null) {
                            // Error Handling
                            //console.log("Error creating object");
                        }
                        else {
                            sprite.x = -40;//column*40;
                            sprite.y = -40;//row*40;
                            sprite.width = 15;
                            sprite.height = 15;
                            sprite.active = false;
                            sprite.objectName = compName;
                        }
                    }
                    for(var big_explosion_count = 0; big_explosion_count < 32; big_explosion_count++) {
                        compName = "big_explosion_" + big_explosion_count;
                        sprite = component.createObject(canvas);
                        if (sprite == null) {
                            // Error Handling
                            //console.log("Error creating object");
                        }
                        else {
                            sprite.x = -50;//column*40;
                            sprite.y = -50;//row*40;
                            sprite.width = 50;
                            sprite.height = 50;
                            sprite.active = false;
                            sprite.objectName = compName;
                        }
                    }
                    for (var alien_count = 0; alien_count < 20; alien_count++) {

                        compName = "alien_" + alien_count;
                        sprite = component.createObject(canvas);
                        if (sprite == null) {
                            // Error Handling
                            //console.log("Error creating object");
                        }
                        else {
                            sprite.x = -40;//column*40;
                            sprite.y = -40;//row*40;
                            sprite.active = false;
                            sprite.objectName = compName;
                        }
                    }
                    component = Qt.createComponent("GameOver.qml");
                    compName = "game_over";
                    sprite = component.createObject(canvas);
                    sprite.objectName = compName;

                }

   // }
//    Rectangle{
//        color : "#FF000000"
//        z:2
//    Image {
//        id: name
//        x: 580
//        y: 20
//        //z: 2
//        source: "Images/alien_panzer_nord.png"
//    }
//    }
}
