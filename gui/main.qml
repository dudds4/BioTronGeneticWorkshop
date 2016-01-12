import QtQuick 2.3
import QtQuick.Window 2.2

import com.biotron.boardcontroller 1.0

Window {
    visible: true
    width: 640
    height: 640

    Rectangle {
        color: "gray"
        anchors.fill: parent

        Text {
            text: "Connect 4"
            x: parent.width / 2 - width / 2
            y: 10
            font.pointSize: 20
            color: "#333333"
        }

        Rectangle {
            x: 40
            y: 40
            color: "gray"
            Column {
                Text {
                    text: "Player 1"
                    color: "blue"
                }
                Text {
                    text: "Player 2"
                    color: "red"
                }
            }
        }

        Rectangle {
            color: "black"
            width: parent.width * 2 / 3
            x: parent.width / 6
            y: parent.height / 8 + 50
            height: width

            Column {
                id: boardColumn
                anchors.fill: parent

                spacing: 6
                Repeater {
                    model: 3
                    Connect4Row {
                        sspacing: 6
                        rowDataArray: BoardController.gameBoard
                        offset: index*7
                        width: parent.width

                    }
                }
            }
        }
    }
}

