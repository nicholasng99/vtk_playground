import QtQuick
import QtQuick.Controls

import Style
import Utility

ApplicationWindow {
    visible: true
    title: qsTr("Vtk Playground")
    width: Style.screenWidth
    height: Style.screenHeight

    VtkItem {
        anchors.fill: parent
    }

    Component.onCompleted: {
        console.log(Settings.getValue("Language"));
    }
}
