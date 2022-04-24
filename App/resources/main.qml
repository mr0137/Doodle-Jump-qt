import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import App 1.0

Window {
    id: window
    width: 750
    height: 1334
    visible: true
    title: qsTr("Hello World")

    Item{
        id: root
        anchors.fill: parent

        SceneView{
            anchors.fill: parent
            scene: AppCore.scene
        }

        Button{
            anchors.bottomMargin: 10
            width: 200
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.botton

            onPressed: {
                AppCore.start();
            }
        }
    }
}
