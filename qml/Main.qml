import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Style
import Utility

ApplicationWindow {
    visible: true
    title: qsTr("Vtk Playground")
    width: Style.screenWidth
    height: Style.screenHeight

    ModelViewer {
        id: viewer
        anchors.fill: parent
    }

    RowLayout {
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Slider {
            from: -10
            to: 10
            value: 0
            onValueChanged: {
                viewer.value = value
            }
        }
    }

    Component.onCompleted: {
        console.log(Settings.getValue("Language"));
    }
}
