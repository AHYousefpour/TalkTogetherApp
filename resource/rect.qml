import QtQuick 2.15

Rectangle {
    width: parent.width;
    height: parent.height;
    gradient: Gradient {
        orientation: Gradient.Vertical
        GradientStop {
            position: 0
            color: "#243949"
        }

        GradientStop {
            position: 1
            color: "#517fa4"
        }
    }
}
