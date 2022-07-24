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

    onWidthChanged: {
        AppCore.scene.width = width
    }

    onHeightChanged: {
        AppCore.scene.height = height
    }

    Item{
        id: root
        anchors.fill: parent

        SceneView{
            id: sceneView
            anchors.fill: parent
            keyNegotiator: AppCore.keyNegotiator
            scene: AppCore.scene
            focus: true
        }

        Text {
            anchors.right: sceneView.right
            anchors.top: sceneView.top
            font.pixelSize: 20
            text: "FPS: " + sceneView.currentFPS
        }

        Button{
            anchors.bottomMargin: 10
            width: 200
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.botton
            focus: false
            activeFocusOnTab: false

            onPressed: {
                AppCore.start();
            }
        }
    }
}
