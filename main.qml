import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4

import QtQuick.Controls 1.2 // this for style in TextField


Window {

    visible: true
    width: 640
    height: 480
    title: qsTr("C++ proxy models and QML")


    ColumnLayout {
        id: mainLayout
        anchors.fill: parent

        Rectangle{
            color: "#333238"
            Layout.fillWidth: true
            height: 40
            z: 2
            RowLayout {
                id: rowLayout
                anchors.fill: parent
                anchors.centerIn: parent
                Text {
                    color: "white"
                    text: qsTr("Filter by:")
                }
                ComboBox {
                    id: filterComboRole
                    model: filterModel.getRoleNamesList()
                    Layout.fillWidth: true
                    onCurrentTextChanged: {
                        if(currentText !== ""){
                            const roleCode = filterModel.getRoleCodeFromName( currentText );
                            filterModel.setFilterRole( roleCode );
                        }
                    }
                }
                TextField {
                    placeholderText: "Type here.."
                    Layout.fillWidth: true
                    onTextChanged: filterModel.setTargetString(text)
                }
                Text {
                    color: "white"
                    text: qsTr("Sort by:")
                }
                ComboBox {
                    id: sortComboRole
                    model: filterModel.getRoleNamesList()
                    Layout.fillWidth: true
                    onCurrentTextChanged: {
                        if(currentText !== ""){
                            const roleCode = filterModel.getRoleCodeFromName( currentText );
                            filterModel.setSortOrder( orderSortCheckBox.checked ) // this is neccesry at first
                            filterModel.setSortRole( roleCode );
                        }
                    }
                }
                CheckBox {
                    id: orderSortCheckBox
                    text: "Descending"
                    onCheckedChanged: filterModel.setSortOrder(checked)
                    style: CheckBoxStyle {
                        label: Text {
                            color: "white"
                            text: "Descending"
                        }
                    }
                }
            }
        }

        ListView {
            id: view
            model: filterModel
            Layout.minimumHeight: 25
            Layout.fillHeight: true
            Layout.fillWidth: true
            cacheBuffer: 100
            spacing: 10

            delegate: Rectangle{
                width: parent.width
                radius: 5
                anchors.horizontalCenter: parent.horizontalCenter
                height: 50
                color: Qt.lighter("#333238", 0.8)
                Text {
                    id: nameTxt
                    text: qsTr("Name: %1 <br/>Email: %3").arg(name_role).arg(email_role)
                    color: "#FFFFFF"
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }


}
