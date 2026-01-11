import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs
import ExcelHandler 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 1600
    height: 900

    property int rows: 0
    property int columns: 0
    property int selectedRow: -1
    property string fileType: "stock"  // "stock" or "purchase"

    title: {
        var fileName = "Untitled"
        if (excelHandler.currentFile !== "") {
            var parts = excelHandler.currentFile.split("/")
            fileName = parts[parts.length - 1]
        }
        return "Enstein Stock Manager - " + fileName +
               (excelHandler.hasUnsavedChanges ? " *" : "") +
               (loginDialog.isAuthenticated ? " [Logged In]" : " [Read-Only]")
    }

    ExcelHandler {
        id: excelHandler

        onErrorOccurred: function(error) {
            errorDialog.errorText = error
            errorDialog.open()
        }

        onFileLoaded: function(fileName) {
            statusLabel.text = "✓ Loaded: " + fileName
            statusTimer.restart()
        }

        onFileSaved: function(fileName) {
            statusLabel.text = "✓ Saved: " + fileName
            statusTimer.restart()
        }

        onFileMerged: function(fileName, rowsAdded, rowsUpdated) {
            statusLabel.text = "✓ Merged - Added: " + rowsAdded + ", Updated: " + rowsUpdated
            statusTimer.restart()
            mergeSuccessDialog.fileName = fileName
            mergeSuccessDialog.rowsAdded = rowsAdded
            mergeSuccessDialog.rowsUpdated = rowsUpdated
            mergeSuccessDialog.open()
        }

        onSearchResultFound: function(row) {
            root.selectedRow = row
        }
    }

    /* ================= DIALOGS ================= */

    Dialog {
        id: errorDialog
        title: "Error"
        modal: true
        standardButtons: Dialog.Ok
        anchors.centerIn: parent
        width: 400

        property alias errorText: errorLabel.text

        Label {
            id: errorLabel
            wrapMode: Text.WordWrap
            width: parent.width
        }
    }

    Dialog {
        id: searchDialog
        title: "🔍 Search Parts"
        modal: true
        standardButtons: Dialog.Close
        anchors.centerIn: parent
        width: 600
        height: 500

        ColumnLayout {
            anchors.fill: parent
            spacing: 10

            Label {
                text: "Search by Part Name, Part No, or Vendor:"
                font.bold: true
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                TextField {
                    id: searchField
                    Layout.fillWidth: true
                    placeholderText: "Enter search text..."
                    selectByMouse: true
                    Keys.onReturnPressed: searchButton.clicked()
                }

                Button {
                    id: searchButton
                    text: "Search"
                    highlighted: true
                    onClicked: {
                        var results = excelHandler.searchAllMatches(searchField.text)
                        searchResultsModel.clear()

                        for (var i = 0; i < results.length; i++) {
                            searchResultsModel.append(results[i])
                        }

                        if (results.length === 0) {
                            statusLabel.text = "No results found for: " + searchField.text
                        } else {
                            statusLabel.text = "Found " + results.length + " result(s)"
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                border.color: "#bdc3c7"
                border.width: 1
                color: "#ecf0f1"

                ListView {
                    id: searchResultsList
                    anchors.fill: parent
                    anchors.margins: 5
                    clip: true
                    spacing: 5

                    model: ListModel {
                        id: searchResultsModel
                    }

                    delegate: Rectangle {
                        width: searchResultsList.width - 10
                        height: 70
                        color: "white"
                        border.color: "#3498db"
                        border.width: 1
                        radius: 5

                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 8
                            spacing: 2

                            Label {
                                text: "📦 " + model.partName
                                font.bold: true
                                font.pixelSize: 13
                                color: "#2c3e50"
                            }

                            Label {
                                text: "Part No: " + model.partNo
                                font.pixelSize: 11
                                color: "#7f8c8d"
                            }

                            RowLayout {
                                Label {
                                    text: "Stock: " + model.stock
                                    font.pixelSize: 11
                                    color: "#27ae60"
                                    font.bold: true
                                }

                                Label {
                                    text: " | Vendor: " + model.vendor
                                    font.pixelSize: 11
                                    color: "#7f8c8d"
                                }
                            }
                        }

                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                root.selectedRow = model.row
                                searchDialog.close()
                                statusLabel.text = "Selected: " + model.partName
                            }
                        }
                    }
                }

                Label {
                    anchors.centerIn: parent
                    text: "No results"
                    visible: searchResultsModel.count === 0
                    color: "#95a5a6"
                    font.pixelSize: 14
                }
            }

            Label {
                text: "💡 Tip: Click on a result to select that row"
                font.pixelSize: 10
                color: "#7f8c8d"
            }
        }

        onOpened: {
            searchField.focus = true
            searchField.selectAll()
        }
    }

    FileDialog {
        id: openDialog
        title: "Open Excel File"
        nameFilters: ["Excel files (*.xlsx *.xls)", "All files (*)"]
        fileMode: FileDialog.OpenFile

        onAccepted: {
            if (excelHandler.loadExcel(selectedFile)) {
                rows = excelHandler.model.rowCount()
                columns = excelHandler.model.columnCount()
                selectedRow = -1
                root.fileType = excelHandler.getFileType()
                console.log("📊 File opened - Rows:", rows, "Columns:", columns, "Type:", root.fileType)
            }
        }
    }

    FileDialog {
        id: saveDialog
        title: "Save Excel File"
        fileMode: FileDialog.SaveFile
        nameFilters: ["Excel files (*.xlsx)", "All files (*)"]
        defaultSuffix: "xlsx"

        onAccepted: {
            excelHandler.saveExcel(selectedFile)
        }
    }

    FileDialog {
        id: setPermanentDialog
        title: "Set Permanent Stock File"
        nameFilters: ["Excel files (*.xlsx *.xls)", "All files (*)"]
        fileMode: FileDialog.OpenFile

        onAccepted: {
            if (excelHandler.setPermanentFile(selectedFile)) {
                if (excelHandler.loadPermanentFile()) {
                    rows = excelHandler.model.rowCount()
                    columns = excelHandler.model.columnCount()
                    root.fileType = excelHandler.getFileType()
                    statusLabel.text = "✓ Permanent file set and loaded"
                    statusTimer.restart()
                    console.log("📊 Loaded - Rows:", rows, "Columns:", columns, "Type:", root.fileType)
                } else {
                    statusLabel.text = "❌ Failed to load permanent file"
                }
            }
        }
    }

    FileDialog {
        id: appendFileDialog
        title: "Select Purchase File to Merge"
        nameFilters: ["Excel files (*.xlsx *.xls)", "All files (*)"]
        fileMode: FileDialog.OpenFile

        onAccepted: {
            if (excelHandler.appendFromFile(selectedFile)) {
                rows = excelHandler.model.rowCount()
                columns = excelHandler.model.columnCount()
            }
        }
    }

    // New Stock File Dialog
    Dialog {
        id: newStockFileDialog
        title: "Create New Stock File"
        standardButtons: Dialog.Ok | Dialog.Cancel
        modal: true
        anchors.centerIn: parent

        ColumnLayout {
            spacing: 10

            Label {
                text: "📦 Stock File (with Stock column)"
                font.bold: true
                font.pixelSize: 14
                color: "#27ae60"
            }

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#27ae60"
            }

            Label {
                text: "Number of Rows:"
                font.bold: true
            }
            SpinBox {
                id: stockRowsSpin
                from: 1
                to: 1000
                value: 15
                editable: true
            }

            Label {
                text: "Columns: Part Name | Part No | Stock | Department | Prepared | Approved | Vendor | File"
                font.pixelSize: 10
                color: "#7f8c8d"
                wrapMode: Text.WordWrap
            }
        }

        onAccepted: {
            excelHandler.createStockFile(stockRowsSpin.value)
            rows = excelHandler.model.rowCount()
            columns = excelHandler.model.columnCount()
            selectedRow = -1
            root.fileType = "stock"
            statusLabel.text = "✓ Created new Stock file: " + rows + " rows"
        }
    }

    // New Purchase File Dialog
    Dialog {
        id: newPurchaseFileDialog
        title: "Create New Purchase File"
        standardButtons: Dialog.Ok | Dialog.Cancel
        modal: true
        anchors.centerIn: parent

        ColumnLayout {
            spacing: 10

            Label {
                text: "🛒 Purchase File (with Purchase column)"
                font.bold: true
                font.pixelSize: 14
                color: "#3498db"
            }

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#3498db"
            }

            Label {
                text: "Number of Rows:"
                font.bold: true
            }
            SpinBox {
                id: purchaseRowsSpin
                from: 1
                to: 1000
                value: 15
                editable: true
            }

            Label {
                text: "Columns: Part Name | Part No | Purchase | Department | Prepared | Approved | Vendor | File"
                font.pixelSize: 10
                color: "#7f8c8d"
                wrapMode: Text.WordWrap
            }

            Label {
                text: "💡 Use this file to record purchases, then merge with Stock file"
                font.pixelSize: 10
                color: "#3498db"
                wrapMode: Text.WordWrap
            }
        }

        onAccepted: {
            excelHandler.createPurchaseFile(purchaseRowsSpin.value)
            rows = excelHandler.model.rowCount()
            columns = excelHandler.model.columnCount()
            selectedRow = -1
            root.fileType = "purchase"
            statusLabel.text = "✓ Created new Purchase file: " + rows + " rows"
        }
    }

    // Add Item Dialog
    Dialog {
        id: addItemDialog
        title: "Add Stock Item"
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel
        anchors.centerIn: parent
        width: 450

        ColumnLayout {
            spacing: 10
            width: parent.width

            Label {
                text: "📦 Add New Stock Item"
                font.bold: true
                font.pixelSize: 14
            }

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#ccc"
            }

            Label {
                text: "Part Name:"
                font.pixelSize: 12
            }
            TextField {
                id: partNameField
                Layout.fillWidth: true
                placeholderText: "e.g., Microcontroller"
                selectByMouse: true
            }

            Label {
                text: "Department:"
                font.pixelSize: 12
            }
            ComboBox {
                id: categoryField
                Layout.fillWidth: true
                editable: true
                model: ["Electronics", "Mechanical", "Hardware", "Software", "Other"]
            }

            Label {
                text: "Stock Quantity:"
                font.pixelSize: 12
            }
            SpinBox {
                id: quantityField
                Layout.fillWidth: true
                from: 1
                to: 10000
                value: 1
                editable: true
            }

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#ccc"
            }

            Label {
                text: "💡 If part exists, stock will be added to current quantity"
                font.pixelSize: 10
                color: "#7f8c8d"
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }
        }

        onAccepted: {
            if (partNameField.text.trim() === "") {
                errorDialog.errorText = "Part name is required!"
                errorDialog.open()
                return
            }

            excelHandler.addNewItem(
                partNameField.text.trim(),
                categoryField.currentText,
                quantityField.value,
                0
            )

            rows = excelHandler.model.rowCount()
            columns = excelHandler.model.columnCount()

            statusLabel.text = "✓ Added: " + partNameField.text
            statusTimer.restart()

            partNameField.text = ""
            categoryField.currentIndex = 0
            quantityField.value = 1
        }

        onOpened: {
            partNameField.focus = true
        }
    }

    Dialog {
        id: mergeSuccessDialog
        title: "✓ Merge Complete"
        modal: true
        standardButtons: Dialog.Ok
        anchors.centerIn: parent

        property string fileName: ""
        property int rowsAdded: 0
        property int rowsUpdated: 0

        ColumnLayout {
            spacing: 10

            Label {
                text: "✓ Successfully merged!"
                font.bold: true
                font.pixelSize: 14
                color: "#27ae60"
            }

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#27ae60"
            }

            Label {
                text: "File: " + mergeSuccessDialog.fileName
                font.pixelSize: 12
            }

            Label {
                text: "Rows updated: " + mergeSuccessDialog.rowsUpdated
                font.bold: true
                color: "#3498db"
            }

            Label {
                text: "Rows added: " + mergeSuccessDialog.rowsAdded
                font.bold: true
                color: "#27ae60"
            }

            Label {
                text: "Total rows: " + rows
                font.pixelSize: 12
            }
        }
    }

    Dialog {
        id: loginDialog
        title: "Authorization Required"
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel
        anchors.centerIn: parent

        property bool isAuthenticated: false
        property string correctUsername: "admin"
        property string correctPassword: "admin123"

        ColumnLayout {
            spacing: 15

            Label {
                text: "🔐 Enter credentials to enable editing"
                font.bold: true
                font.pixelSize: 14
            }

            Label {
                text: "Username:"
                font.pixelSize: 12
            }
            TextField {
                id: usernameField
                placeholderText: "admin"
                Layout.fillWidth: true
                selectByMouse: true
            }

            Label {
                text: "Password:"
                font.pixelSize: 12
            }
            TextField {
                id: passwordField
                placeholderText: "password"
                echoMode: TextInput.Password
                Layout.fillWidth: true
                selectByMouse: true
                Keys.onReturnPressed: loginDialog.accept()
            }

            Label {
                id: loginError
                text: ""
                color: "#e74c3c"
                visible: text !== ""
            }
        }

        onAccepted: {
            if (usernameField.text === correctUsername &&
                passwordField.text === correctPassword) {
                isAuthenticated = true
                usernameField.text = ""
                passwordField.text = ""
                statusLabel.text = "✓ Login successful"
                statusTimer.restart()
            } else {
                loginError.text = "❌ Invalid credentials"
                passwordField.text = ""
                loginDialog.open()
            }
        }
    }

    Dialog {
        id: cloudSettingsDialog
        title: "☁️ Cloud Sync Settings"
        modal: true
        width: 500

        ColumnLayout {
            spacing: 20
            width: parent.width

            // Cloud Folder Section
            Label {
                text: "Cloud Folder Path:"
                font.bold: true
            }

            RowLayout {
                Layout.fillWidth: true
                TextField {
                    id: cloudFolderField
                    text: excelHandler.cloudFolder
                    placeholderText: "/home/ensteinrobotsystem/Dropbox/Stock"
                    Layout.fillWidth: true
                }
                Button {
                    text: "Browse"
                    onClicked: cloudFolderDialog.open()
                }
            }

            // User Info Section
            Label {
                text: "User Information:"
                font.bold: true
            }

            GridLayout {
                columns: 2
                rowSpacing: 10
                columnSpacing: 10
                Layout.fillWidth: true

                Label { text: "Name:" }
                TextField {
                    id: userNameField
                    text: excelHandler.currentUser
                    Layout.fillWidth: true
                }

                Label { text: "Role:" }
                ComboBox {
                    id: userRoleCombo
                    model: ["owner", "editor", "viewer"]
                    Layout.fillWidth: true
                    Component.onCompleted: {
                        if (excelHandler.userRole === "owner") currentIndex = 0
                        else if (excelHandler.userRole === "editor") currentIndex = 1
                        else currentIndex = 2
                    }
                }
            }

            // Status Section
            Rectangle {
                Layout.fillWidth: true
                height: 60
                color: "#ecf0f1"
                radius: 5

                ColumnLayout {
                    anchors.centerIn: parent
                    Label { text: "Last Synced: " + excelHandler.lastSyncTime }
                    Label { text: "Status: " + excelHandler.syncStatus }
                }
            }

            // Help
            Label {
                text: "💡 Tip: Use Dropbox folder"
                font.italic: true
                Layout.fillWidth: true
                wrapMode: Text.WordWrap
            }

            // Buttons
            RowLayout {
                Layout.alignment: Qt.AlignRight
                Button {
                    text: "Cancel"
                    onClicked: cloudSettingsDialog.close()
                }
                Button {
                    text: "Save"
                    highlighted: true
                    onClicked: {
                        excelHandler.setCloudFolder(cloudFolderField.text)
                        excelHandler.setCurrentUser(userNameField.text)
                        excelHandler.setUserRole(userRoleCombo.currentText)
                        statusLabel.text = "✅ Settings saved"
                        cloudSettingsDialog.close()
                    }
                }
            }
        }
    }

    FolderDialog {
        id: cloudFolderDialog
        title: "Select Cloud Sync Folder"
        onAccepted: {
            var path = selectedFolder.toString()
            path = path.replace("file://", "")
            cloudFolderField.text = path
        }
    }
    /* ================= TOOLBAR ================= */
    header: ToolBar {
        background: Rectangle {
            color: "#34495e"
        }

        RowLayout {
            anchors.fill: parent
            spacing: 5

            ToolButton {
                text: "📦 Create Stock"
                onClicked: newStockFileDialog.open()
                ToolTip.visible: hovered
                ToolTip.text: "Create new stock file"

                contentItem: Text {
                    text: parent.text
                    color: "#27ae60"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                }
            }

            // ToolButton {
            //     text: "🛒 Create Purchase"
            //     onClicked: newPurchaseFileDialog.open()
            //     ToolTip.visible: hovered
            //     ToolTip.text: "Create new purchase file"

            //     contentItem: Text {
            //         text: parent.text
            //         color: "#3498db"
            //         horizontalAlignment: Text.AlignHCenter
            //         verticalAlignment: Text.AlignVCenter
            //         font.bold: true
            //     }
            // }

            ToolButton {
                text: "📂 Open"
                onClicked: openDialog.open()
                ToolTip.visible: hovered
                ToolTip.text: "Open Excel file"

                contentItem: Text {
                    text: parent.text
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            ToolSeparator {
                contentItem: Rectangle {
                    implicitWidth: 1
                    implicitHeight: 24
                    color: "#7f8c8d"
                }
            }

            ToolButton {
                text: "📌 Set Permanent"
                enabled: loginDialog.isAuthenticated
                onClicked: setPermanentDialog.open()
                contentItem: Text {
                    text: parent.text
                    color: parent.enabled ? "#f39c12" : "#7f8c8d"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                }
            }

            // ToolButton {
            //     text: "🔄 Merge Purchase File"
            //     enabled: loginDialog.isAuthenticated && excelHandler.permanentFile !== ""
            //     onClicked: appendFileDialog.open()
            //     contentItem: Text {
            //         text: parent.text
            //         color: parent.enabled ? "#9b59b6" : "#7f8c8d"
            //         horizontalAlignment: Text.AlignHCenter
            //         verticalAlignment: Text.AlignVCenter
            //         font.bold: true
            //     }
            // }

            ToolSeparator {
                contentItem: Rectangle {
                    implicitWidth: 1
                    implicitHeight: 24
                    color: "#7f8c8d"
                }
            }

            ToolButton {
                text: "💾 Save"
                enabled: excelHandler.currentFile !== "" && loginDialog.isAuthenticated
                onClicked: excelHandler.saveExcel("")
                contentItem: Text {
                    text: parent.text
                    color: parent.enabled ? "white" : "#7f8c8d"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            ToolButton {
                text: "💾 Save As"
                enabled: loginDialog.isAuthenticated
                onClicked: saveDialog.open()
                contentItem: Text {
                    text: parent.text
                    color: parent.enabled ? "white" : "#7f8c8d"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            ToolSeparator {
                contentItem: Rectangle {
                    implicitWidth: 1
                    implicitHeight: 24
                    color: "#7f8c8d"
                }
            }

            ToolButton {
                text: "🔍 Search"
                onClicked: searchDialog.open()
                contentItem: Text {
                    text: parent.text
                    color: "#3498db"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                }
            }

            ToolButton {
                text: loginDialog.isAuthenticated ? "🔓 Logout" : "🔒 Login"
                onClicked: loginDialog.isAuthenticated ? (loginDialog.isAuthenticated = false) : loginDialog.open()
                ToolTip.visible: hovered
                ToolTip.text: loginDialog.isAuthenticated ? "Logout" : "Login to edit"

                contentItem: Text {
                    text: parent.text
                    color: loginDialog.isAuthenticated ? "#2ecc71" : "#e74c3c"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                }
            }

            ToolButton {
                text: "➕ Add Item"
                enabled: loginDialog.isAuthenticated
                onClicked: addItemDialog.open()
                ToolTip.visible: hovered
                ToolTip.text: "Add new stock item"

                contentItem: Text {
                    text: parent.text
                    color: parent.enabled ? "#3498db" : "#7f8c8d"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                }
            }

            ToolButton {
                text: "➕ Row"
                enabled: loginDialog.isAuthenticated
                onClicked: {
                    excelHandler.model.addRow()
                    rows = excelHandler.model.rowCount()
                    statusLabel.text = "Added new row"
                }
                ToolTip.visible: hovered
                ToolTip.text: "Add empty row"

                contentItem: Text {
                    text: parent.text
                    color: parent.enabled ? "white" : "#7f8c8d"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            ToolButton {
                text: "➕ Col"
                enabled: loginDialog.isAuthenticated
                onClicked: {
                    excelHandler.model.addColumn()
                    columns = excelHandler.model.columnCount()
                    statusLabel.text = "Added new column"
                }
                ToolTip.visible: hovered
                ToolTip.text: "Add empty column"

                contentItem: Text {
                    text: parent.text
                    color: parent.enabled ? "white" : "#7f8c8d"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Item { Layout.fillWidth: true }

            Label {
                text: loginDialog.isAuthenticated ?
                      (excelHandler.hasUnsavedChanges ? "● Unsaved Changes" : "✓ All Saved") :
                      "🔒 Read-Only"
                color: loginDialog.isAuthenticated ?
                       (excelHandler.hasUnsavedChanges ? "#e74c3c" : "#2ecc71") :
                       "#f39c12"
                font.bold: true
                font.pixelSize: 13
            }

            Item { Layout.fillWidth: true }

            Item { Layout.fillWidth: true }

            // User Info
            Label {
                text: "👤 " + excelHandler.currentUser + " (" + excelHandler.userRole + ")"
                color: "white"
            }

            // Sync Status
            Label {
                text: {
                    if (excelHandler.syncStatus === "synced") return "🟢 Synced"
                    if (excelHandler.syncStatus === "syncing") return "🟡 Syncing..."
                    if (excelHandler.syncStatus === "conflict") return "🔴 Conflict"
                    return "⚪ Offline"
                }
                color: "white"
            }

            // Sync To Cloud
            ToolButton {
                text: "⬆️"
                enabled: excelHandler.canEdit()
                onClicked: {
                    if (excelHandler.syncToCloud()) {
                        statusLabel.text = "✅ Synced to cloud"
                    }
                }
                ToolTip.visible: hovered
                ToolTip.text: "Sync To Cloud"
            }

            // Sync From Cloud
            ToolButton {
                text: "⬇️"
                onClicked: {
                    if (excelHandler.syncFromCloud()) {
                        statusLabel.text = "✅ Downloaded from cloud"
                        rows = excelHandler.model.rowCount()
                        columns = excelHandler.model.columnCount()
                    }
                }
                ToolTip.visible: hovered
                ToolTip.text: "Sync From Cloud"
            }

            // Settings
            ToolButton {
                text: "⚙️"
                onClicked: cloudSettingsDialog.open()
                ToolTip.visible: hovered
                ToolTip.text: "Cloud Settings"
            }

        }
    }

    /* ================= MAIN TABLE ================= */
    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            color: "#fff3cd"
            border.color: "#ffc107"
            border.width: 2
            visible: excelHandler.permanentFile === ""

            RowLayout {
                anchors.fill: parent
                anchors.margins: 8
                spacing: 10

                Label {
                    text: "⚠️"
                    font.pixelSize: 20
                }

                Label {
                    text: "No permanent stock file set. Click '📌 Set Permanent' to select your main stock database file."
                    font.pixelSize: 13
                    color: "#856404"
                    Layout.fillWidth: true
                }

                Button {
                    text: "Set Now"
                    highlighted: true
                    enabled: loginDialog.isAuthenticated
                    onClicked: setPermanentDialog.open()

                    background: Rectangle {
                        color: parent.enabled ? "#ffc107" : "#ccc"
                        radius: 4
                    }

                    contentItem: Text {
                        text: parent.text
                        color: "#856404"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.bold: true
                    }
                }
            }
        }

        // Column Headers (9 columns - NO Purchase)
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 35
            color: "#2c3e50"

            Row {
                anchors.fill: parent
                spacing: 0

                Rectangle {
                    width: 50
                    height: 35
                    color: "#2c3e50"
                    border.color: "#1a252f"

                    Text {
                        anchors.centerIn: parent
                        text: "#"
                        color: "white"
                        font.bold: true
                    }
                }

                Repeater {
                    model: 7  // 7 columns

                    Rectangle {
                        width: {
                            var widths = [380, 200, 120, 160, 180, 180, 300]  // Part Name wider, Vendor wider
                            return widths[index]
                        }
                        height: 35
                        color: "#34495e"
                        border.color: "#2c3e50"

                        Text {
                            anchors.centerIn: parent
                            text: {
                                var headers = ["Part Name", "Part No",
                                             root.fileType === "purchase" ? "Purchase" : "Stock",
                                             "Department", "Prepared", "Approved", "Vendor"]
                                return headers[index]
                            }
                            color: "white"
                            font.bold: true
                            font.pixelSize: 12
                        }
                    }
                }
            }
        }

        // Data Area
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            Column {
                spacing: 0

                Repeater {
                    model: root.rows

                    Row {
                        spacing: 0
                        property int r: index

                        Rectangle {
                            width: 50
                            height: 35
                            color: root.selectedRow === r ? "#27ae60" : "#95a5a6"
                            border.color: "#7f8c8d"

                            Text {
                                anchors.centerIn: parent
                                text: r + 1
                                color: root.selectedRow === r ? "white" : "#2c3e50"
                                font.bold: root.selectedRow === r
                            }

                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: root.selectedRow = r
                            }
                        }

                        Repeater {
                            model: 7  // 7 columns

                            Rectangle {
                                width: {
                                    var widths = [380, 200, 120, 160, 180, 180, 300]  // Part Name wider, Vendor wider
                                    return widths[index]
                                }
                                height: 35
                                color: root.selectedRow === r ? "#d5f4e6" : "white"
                                border.color: "#dfe6e9"

                                property int c: index

                                // Regular text input
                                TextInput {
                                    visible: true  // Show for all 7 columns
                                    anchors.fill: parent
                                    anchors.margins: 4
                                    verticalAlignment: Text.AlignVCenter
                                    selectByMouse: true
                                    enabled: loginDialog.isAuthenticated

                                    text: {
                                        var v = excelHandler.model.getData(r, c)
                                        return v === null || v === undefined ? "" : v.toString()
                                    }

                                    color: enabled ? "black" : "#95a5a6"
                                    font.pixelSize: 16

                                    onEditingFinished: {
                                        if (enabled) {
                                            excelHandler.model.setDataAt(r, c, text)
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /* ================= FOOTER ================= */
    footer: ToolBar {
        background: Rectangle {
            color: "#ecf0f1"
            border.color: "#bdc3c7"
        }

        RowLayout {
            anchors.fill: parent
            anchors.margins: 5
            spacing: 15

            Label {
                id: statusLabel
                text: "Ready"
                font.pixelSize: 12
                color: "#2c3e50"
            }

            Timer {
                id: statusTimer
                interval: 5000
                onTriggered: statusLabel.text = "Ready"
            }

            Rectangle {
                width: 1
                height: 20
                color: "#bdc3c7"
            }

            Label {
                text: "Rows: " + rows
                font.bold: true
                color: "#34495e"
            }

            Item { Layout.fillWidth: true }

            Label {
                text: excelHandler.permanentFile !== "" ?
                      "📌 " + excelHandler.getFileName() :
                      "⚠️ No permanent file"
                color: excelHandler.permanentFile !== "" ? "#27ae60" : "#e67e22"
                font.bold: excelHandler.permanentFile !== ""
            }
        }
    }

    /* ================= INITIALIZATION ================= */
    Component.onCompleted: {
        console.log("========================================")
        console.log("Stock Management System Initializing...")

        var hasPermanent = excelHandler.hasSavedPermanentFile()
        console.log("Has saved permanent file:", hasPermanent)
        // excelHandler.setCloudFolder("/home/ensteinrobotsystem/Downloads")
        // excelHandler.setCurrentUser("Admin")
        //     excelHandler.setUserRole("owner")
        if (hasPermanent) {
            console.log("Loading permanent file:", excelHandler.getSavedPermanentPath())
            var loaded = excelHandler.loadPermanentFile()

            if (loaded) {
                rows = excelHandler.model.rowCount()
                columns = excelHandler.model.columnCount()
                root.fileType = excelHandler.getFileType()
                statusLabel.text = "✓ Loaded permanent file: " + excelHandler.getFileName()
                console.log("✓ Permanent file loaded successfully")
                console.log("Rows:", rows, "Columns:", columns, "Type:", root.fileType)
            } else {
                console.log("✗ Failed to load permanent file")
                excelHandler.createNew(15, 7)  // 7 columns
                rows = excelHandler.model.rowCount()
                columns = excelHandler.model.columnCount()
                root.fileType = "stock"
                statusLabel.text = "⚠️ Could not load saved permanent file - Created new spreadsheet"
            }
        } else {
            console.log("No permanent file saved - Creating new spreadsheet")
            excelHandler.createNew(15, 7)  // 7 columns
            rows = excelHandler.model.rowCount()
            columns = excelHandler.model.columnCount()
            root.fileType = "stock"
            statusLabel.text = "Stock Management System Ready - Please set permanent file"
        }

        statusTimer.restart()
        console.log("System initialized")
        console.log("========================================")
    }
}
