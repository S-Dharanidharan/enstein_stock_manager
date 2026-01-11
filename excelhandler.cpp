#include "excelhandler.h"

// ==================== ExcelTableModel Implementation ====================

ExcelTableModel::ExcelTableModel(QObject *parent)
  : QAbstractTableModel(parent)
{
}

int ExcelTableModel::rowCount(const QModelIndex &parent) const
{
  if (parent.isValid())
    return 0;
  return m_data.size();
}

int ExcelTableModel::columnCount(const QModelIndex &parent) const
{
  if (parent.isValid() || m_data.isEmpty())
    return 0;
  return m_data.first().size();
}

QVariant ExcelTableModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid() || role != Qt::DisplayRole)
    return QVariant();

  if (index.row() >= m_data.size() || index.column() >= m_data[index.row()].size())
    return QVariant();

  return m_data[index.row()][index.column()];
}

bool ExcelTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (!index.isValid() || role != Qt::EditRole)
    return false;

  if (index.row() >= m_data.size() || index.column() >= m_data[index.row()].size())
    return false;

  m_data[index.row()][index.column()] = value;
  emit dataChanged(index, index, {role});
  return true;
}

Qt::ItemFlags ExcelTableModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::NoItemFlags;
  return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QHash<int, QByteArray> ExcelTableModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[Qt::DisplayRole] = "display";
  return roles;
}

void ExcelTableModel::setExcelData(const QVector<QVector<QVariant>> &data)
{
  beginResetModel();
  m_data = data;
  endResetModel();
}

QVector<QVector<QVariant>> ExcelTableModel::getExcelData() const
{
  return m_data;
}

QVariant ExcelTableModel::getData(int row, int column) const
{
  if (row < 0 || row >= m_data.size())
    return QVariant();
  if (column < 0 || column >= m_data[row].size())
    return QVariant();
  return m_data[row][column];
}

bool ExcelTableModel::setDataAt(int row, int column, const QVariant &value)
{
  if (row < 0 || row >= m_data.size())
    return false;
  if (column < 0 || column >= m_data[row].size())
    return false;

  m_data[row][column] = value;
  QModelIndex idx = index(row, column);
  emit dataChanged(idx, idx, {Qt::DisplayRole});
  return true;
}

void ExcelTableModel::addRow()
{
  int cols = m_data.isEmpty() ? 7 : m_data.first().size();
  beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
  QVector<QVariant> newRow(cols);
  m_data.append(newRow);
  endInsertRows();
}

void ExcelTableModel::addColumn()
{
  if (m_data.isEmpty())
    return;

  int cols = m_data.first().size();
  beginInsertColumns(QModelIndex(), cols, cols);
  for (auto &row : m_data) {
    row.append(QVariant());
  }
  endInsertColumns();
}

void ExcelTableModel::clear()
{
  beginResetModel();
  m_data.clear();
  endResetModel();
}

// ==================== ExcelHandler Implementation ====================

ExcelHandler::ExcelHandler(QObject *parent)
  : QObject(parent),
  m_model(new ExcelTableModel(this)),
  m_hasUnsavedChanges(false),
  m_syncEnabled(false),
  m_syncStatus("offline"),
  m_currentUser("User"),
  m_userRole("editor")
{
  connect(m_model, &QAbstractItemModel::dataChanged,
          this, &ExcelHandler::onModelDataChanged);

  initializeUploadsDirectory();
  loadPermanentFileSettings();
  loadCloudSettings();

  qDebug() << "ExcelHandler created - using Excel (.xlsx) format";
  qDebug() << "Current user:" << m_currentUser << "(" << m_userRole << ")";
}

void ExcelHandler::initializeUploadsDirectory()
{
  QString appData = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
  m_uploadsDir = appData + "/uploads";

  QDir dir;
  if (!dir.exists(m_uploadsDir)) {
    dir.mkpath(m_uploadsDir);
    qDebug() << "✓ Created uploads directory:" << m_uploadsDir;
  } else {
    qDebug() << "✓ Uploads directory exists:" << m_uploadsDir;
  }
}

void ExcelHandler::savePermanentFileSettings()
{
  QSettings settings("EinsteinRobotics", "StockManager");
  settings.setValue("permanentFile", m_permanentFile);
  qDebug() << "✓ Saved permanent file path:" << m_permanentFile;
}

void ExcelHandler::loadPermanentFileSettings()
{
  QSettings settings("EinsteinRobotics", "StockManager");
  QString savedPath = settings.value("permanentFile", "").toString();

  if (!savedPath.isEmpty() && QFileInfo::exists(savedPath)) {
    // Check if it's an Excel file
    QFileInfo fileInfo(savedPath);
    QString suffix = fileInfo.suffix().toLower();

    if (suffix == "xlsx" || suffix == "xls") {
      m_permanentFile = savedPath;
      emit permanentFileChanged();
      qDebug() << "✓ Loaded saved permanent file:" << m_permanentFile;
    } else {
      qDebug() << "⚠ Saved file is not Excel format (" << suffix << "), clearing...";
      m_permanentFile = "";
      savePermanentFileSettings();
    }
  } else if (!savedPath.isEmpty()) {
    qDebug() << "⚠ Saved permanent file no longer exists:" << savedPath;
  }
}

QString ExcelHandler::getSavedPermanentPath()
{
  return m_permanentFile;
}

bool ExcelHandler::hasSavedPermanentFile()
{
  return !m_permanentFile.isEmpty() && QFileInfo::exists(m_permanentFile);
}

bool ExcelHandler::setPermanentFile(const QString &filePath)
{
  QString cleanPath = cleanFilePath(filePath);

  qDebug() << "========================================";
  qDebug() << "Setting permanent file:" << cleanPath;

  QFileInfo fileInfo(cleanPath);
  if (!fileInfo.exists()) {
    QString error = "Permanent file does not exist: " + cleanPath;
    qDebug() << "ERROR:" << error;
    emit errorOccurred(error);
    return false;
  }

  // Validate Excel file
  QString suffix = fileInfo.suffix().toLower();
  if (suffix != "xlsx" && suffix != "xls") {
    QString error = "❌ Invalid file type!\n\n"
                    "Permanent file must be Excel format (.xlsx or .xls)\n"
                    "Got: ." + suffix + " file\n\n"
                               "💡 Please select an Excel file (.xlsx)";
    qDebug() << "ERROR:" << error;
    emit errorOccurred(error);
    return false;
  }

  m_permanentFile = cleanPath;
  m_currentFile = cleanPath;
  savePermanentFileSettings();
  emit permanentFileChanged();
  emit currentFileChanged();

  qDebug() << "✓ Permanent file set and saved";
  qDebug() << "========================================";

  return true;
}

bool ExcelHandler::loadPermanentFile()
{
  if (m_permanentFile.isEmpty()) {
    QString error = "No permanent file set. Please use 'Set Permanent' button first.";
    qDebug() << "ERROR:" << error;
    emit errorOccurred(error);
    return false;
  }

  QFileInfo fileInfo(m_permanentFile);
  if (!fileInfo.exists()) {
    QString error = "Permanent file not found:\n" + m_permanentFile +
                    "\n\nThe file may have been moved or deleted.\nPlease set a new permanent file.";
    qDebug() << "ERROR: File does not exist:" << m_permanentFile;

    m_permanentFile = "";
    savePermanentFileSettings();
    emit permanentFileChanged();

    emit errorOccurred(error);
    return false;
  }

  qDebug() << "Loading permanent file:" << m_permanentFile;
  return loadExcel(m_permanentFile);
}

bool ExcelHandler::saveToPermanent()
{
  if (m_permanentFile.isEmpty()) {
    emit errorOccurred("No permanent file set");
    return false;
  }

  return saveExcel(m_permanentFile);
}

int ExcelHandler::findPartByName(const QString &partName)
{
  int rows = m_model->rowCount();
  QString searchName = partName.trimmed().toLower();

  for (int row = 1; row < rows; ++row) {  // Skip header
    QString existingName = m_model->getData(row, 0).toString().trimmed().toLower();  // Column 0 = Part Name
    if (existingName == searchName) {
      return row;
    }
  }

  return -1;
}

bool ExcelHandler::updateExistingPart(int row, const QVector<QVariant> &mergeData)
{
  qDebug() << "  📝 Updating existing part at row:" << row;

  // COLUMN MAPPING (7 columns):
  // Stock file: 0=Part Name, 1=Part No, 2=Stock, 3=Department, 4=Prepared, 5=Approved, 6=Vendor
  // Purchase file: 0=Part Name, 1=Part No, 2=Purchase, 3=Department, 4=Prepared, 5=Approved, 6=Vendor

  // Get current stock (column 2 in stock file)
  int currentStock = m_model->getData(row, 2).toInt();

  // Get purchase from merge file (column 2 in purchase file)
  int purchaseQty = mergeData.size() > 2 ? mergeData[2].toInt() : 0;

  // Calculate new stock = current stock + purchase
  int newStock = currentStock + purchaseQty;

  qDebug() << "    📊 Current Stock:" << currentStock;
  qDebug() << "    ➕ Adding Purchase:" << purchaseQty;
  qDebug() << "    ✅ New Stock:" << newStock;

  // Update stock (column 2)
  m_model->setDataAt(row, 2, newStock);

  // Update other fields if provided in merge file
  if (mergeData.size() > 1 && !mergeData[1].toString().trimmed().isEmpty()) {
    m_model->setDataAt(row, 1, mergeData[1]); // Part No
  }

  if (mergeData.size() > 3 && !mergeData[3].toString().trimmed().isEmpty()) {
    m_model->setDataAt(row, 3, mergeData[3]); // Department
  }

  if (mergeData.size() > 4 && !mergeData[4].toString().trimmed().isEmpty()) {
    m_model->setDataAt(row, 4, mergeData[4]); // Prepared
  }

  if (mergeData.size() > 5 && !mergeData[5].toString().trimmed().isEmpty()) {
    m_model->setDataAt(row, 5, mergeData[5]); // Approved
  }

  if (mergeData.size() > 6 && !mergeData[6].toString().trimmed().isEmpty()) {
    m_model->setDataAt(row, 6, mergeData[6]); // Vendor Name
  }

  return true;
}

bool ExcelHandler::appendFromFile(const QString &filePath)
{
  QString cleanPath = cleanFilePath(filePath);

  qDebug() << "========================================";
  qDebug() << "🔄 Smart merging from:" << cleanPath;

  if (!validateFileStructure(cleanPath)) {
    QString error = "❌ File structure mismatch!\n\n"
                    "You are trying to merge a STOCK file.\n"
                    "Only PURCHASE files can be merged.\n\n"
                    "📋 Purchase file should have:\n"
                    "Part Name | Part No | Purchase | Department | Prepared | Approved | Vendor | File\n\n"
                    "💡 Use '🛒 Create Purchase' button to make a purchase file.";
    qDebug() << "ERROR:" << error;
    emit errorOccurred(error);
    return false;
  }

  QXlsx::Document xlsx(cleanPath);
  if (!xlsx.load()) {
    emit errorOccurred("Failed to load file");
    return false;
  }

  QXlsx::Worksheet *sheet = xlsx.currentWorksheet();
  if (!sheet) {
    emit errorOccurred("No worksheet found");
    return false;
  }

  QXlsx::CellRange range = sheet->dimension();

  int rowsAdded = 0;
  int rowsUpdated = 0;
  QSet<QString> processedParts;

  qDebug() << "";
  qDebug() << "🔍 Processing purchase file rows...";

  // Process merge file rows (skip header)
  for (int row = 2; row <= range.lastRow(); ++row) {
    QVector<QVariant> rowData;

    // Read 7 columns from purchase file (removed File Upload)
    // Columns: Part Name | Part No | Purchase | Department | Prepared | Approved | Vendor
    for (int col = 1; col <= 7; ++col) {
      auto cell = sheet->cellAt(row, col);
      rowData.append(cell ? cell->value() : QVariant());
    }

    // Column 0 = Part Name (1st column in Excel)
    QString partName = rowData.size() > 0 ? rowData[0].toString().trimmed() : "";

    if (partName.isEmpty()) {
      qDebug() << "  ⏭️ Row" << row << ": Skipping (empty part name)";
      continue;
    }

    qDebug() << "";
    qDebug() << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
    qDebug() << "📦 Row" << row << ":" << partName;

    // Skip duplicates within same merge file
    QString partNameLower = partName.toLower();
    if (processedParts.contains(partNameLower)) {
      qDebug() << "  ⚠️  Duplicate in purchase file - SKIPPED";
      continue;
    }

    processedParts.insert(partNameLower);

    // Show purchase data
    qDebug() << "  📄 Purchase Data:";
    qDebug() << "    Part Name:" << (rowData.size() > 0 ? rowData[0].toString() : "");
    qDebug() << "    Part No:" << (rowData.size() > 1 ? rowData[1].toString() : "");
    qDebug() << "    Purchase Qty:" << (rowData.size() > 2 ? rowData[2].toInt() : 0);
    qDebug() << "    Department:" << (rowData.size() > 3 ? rowData[3].toString() : "");
    qDebug() << "    Vendor:" << (rowData.size() > 6 ? rowData[6].toString() : "");

    // Check if part already exists in permanent stock file
    int existingRow = findPartByName(partName);

    if (existingRow != -1) {
      // 📝 UPDATE EXISTING PART
      qDebug() << "  ✓ Part EXISTS in stock (Row" << existingRow << ")";
      updateExistingPart(existingRow, rowData);
      rowsUpdated++;
      qDebug() << "  ✅ Updated successfully";
    } else {
      // ➕ ADD NEW PART
      qDebug() << "  ✓ Part is NEW (not in stock)";
      m_model->addRow();
      int newRow = m_model->rowCount() - 1;

      int purchaseQty = rowData.size() > 2 ? rowData[2].toInt() : 0;

      qDebug() << "  📝 Adding to row" << newRow << "with initial stock:" << purchaseQty;

      // For NEW parts: Stock = Purchase quantity from merge file
      // COLUMN MAPPING: 0=Part Name, 1=Part No, 2=Stock, 3=Department, 4=Prepared, 5=Approved, 6=Vendor (7 columns total)
      m_model->setDataAt(newRow, 0, partName);                                       // Part Name
      m_model->setDataAt(newRow, 1, rowData.size() > 1 ? rowData[1] : QVariant());  // Part No
      m_model->setDataAt(newRow, 2, purchaseQty);                                    // Stock = Purchase
      m_model->setDataAt(newRow, 3, rowData.size() > 3 ? rowData[3] : QVariant());  // Department
      m_model->setDataAt(newRow, 4, rowData.size() > 4 ? rowData[4] : QVariant());  // Prepared
      m_model->setDataAt(newRow, 5, rowData.size() > 5 ? rowData[5] : QVariant());  // Approved
      m_model->setDataAt(newRow, 6, rowData.size() > 6 ? rowData[6] : QVariant());  // Vendor Name

      rowsAdded++;
      qDebug() << "  ✅ Added successfully";
    }
  }

  qDebug() << "========================================";
  qDebug() << "✅ Merge complete:";
  qDebug() << "  📝 Updated:" << rowsUpdated << "parts";
  qDebug() << "  ➕ Added:" << rowsAdded << "new parts";
  qDebug() << "  📊 Total rows:" << m_model->rowCount();
  qDebug() << "========================================";

  if (!m_permanentFile.isEmpty()) {
    qDebug() << "💾 Auto-saving to permanent file...";
    saveToPermanent();
  }

  emit fileMerged(QFileInfo(cleanPath).fileName(), rowsAdded, rowsUpdated);

  return true;
}

int ExcelHandler::searchPartName(const QString &partName)
{
  int row = findPartByName(partName);

  if (row != -1) {
    qDebug() << "✓ Found:" << partName << "at row" << row;
    emit searchResultFound(row);
  } else {
    qDebug() << "✗ Not found:" << partName;
  }

  return row;
}

QVariantList ExcelHandler::searchAllMatches(const QString &searchText)
{
  QVariantList results;
  int rows = m_model->rowCount();
  QString search = searchText.trimmed().toLower();

  for (int row = 1; row < rows; ++row) {
    QString partName = m_model->getData(row, 0).toString().toLower();  // Column 0
    QString partNo = m_model->getData(row, 1).toString().toLower();    // Column 1
    QString vendor = m_model->getData(row, 6).toString().toLower();    // Column 6

    if (partName.contains(search) || partNo.contains(search) || vendor.contains(search)) {
      QVariantMap result;
      result["row"] = row;
      result["partName"] = m_model->getData(row, 0);  // Column 0
      result["partNo"] = m_model->getData(row, 1);    // Column 1
      result["stock"] = m_model->getData(row, 2);     // Column 2
      result["vendor"] = m_model->getData(row, 6);    // Column 6
      results.append(result);
    }
  }

  qDebug() << "Search '" << searchText << "' found" << results.size() << "results";

  return results;
}

bool ExcelHandler::uploadFileForPart(int row, const QString &filePath)
{
  Q_UNUSED(row)
  Q_UNUSED(filePath)

  qDebug() << "⚠ File upload feature removed - use cloud sync instead";
  emit errorOccurred("File upload removed. Please use cloud sync to share files.");
  return false;
}

QString ExcelHandler::getUploadedFilePath(int row)
{
  Q_UNUSED(row)
  return "";
}

bool ExcelHandler::openUploadedFile(int row)
{
  Q_UNUSED(row)
  emit errorOccurred("File upload removed. Please use cloud sync to share files.");
  return false;
}

bool ExcelHandler::hasUploadedFile(int row)
{
  Q_UNUSED(row)
  return false;
}

void ExcelHandler::createNew(int rows, int cols)
{
  qDebug() << "Creating new spreadsheet:" << rows << "x" << cols;

  QVector<QVector<QVariant>> data;
  data.reserve(rows);

  // Stock file header - 7 columns (removed File Upload)
  QVector<QVariant> header = {"Part Name", "Part No", "Stock",
                              "Department", "Prepared", "Approved", "Vendor Name"};
  data.append(header);

  for (int i = 1; i < rows; ++i) {
    QVector<QVariant> row(7); // 7 columns
    data.append(row);
  }

  m_model->setExcelData(data);
  m_currentFile = "";
  setUnsavedChanges(false);

  emit currentFileChanged();

  qDebug() << "✓ New spreadsheet created with 7 columns";
}

void ExcelHandler::createStockFile(int rows)
{
  qDebug() << "========================================";
  qDebug() << "📦 Creating new STOCK file (Excel format)";
  qDebug() << "========================================";
  qDebug() << "Rows:" << rows;

  QVector<QVector<QVariant>> data;
  data.reserve(rows);

  // STOCK FILE header - 7 columns (removed File Upload)
  QVector<QVariant> header = {"Part Name", "Part No", "Stock",
                              "Department", "Prepared", "Approved", "Vendor Name"};
  data.append(header);

  qDebug() << "Header: Part Name | Part No | STOCK | Department | Prepared | Approved | Vendor";

  for (int i = 1; i < rows; ++i) {
    QVector<QVariant> row(7);
    data.append(row);
  }

  m_model->setExcelData(data);
  m_currentFile = "";
  setUnsavedChanges(false);

  emit currentFileChanged();

  qDebug() << "✓ Stock file created successfully (7 columns - Excel .xlsx)";
  qDebug() << "========================================";
}

void ExcelHandler::createPurchaseFile(int rows)
{
  qDebug() << "========================================";
  qDebug() << "🛒 Creating new PURCHASE file (Excel format)";
  qDebug() << "========================================";
  qDebug() << "Rows:" << rows;

  QVector<QVector<QVariant>> data;
  data.reserve(rows);

  // PURCHASE FILE header - 7 columns (removed File Upload)
  QVector<QVariant> header = {"Part Name", "Part No", "Purchase",
                              "Department", "Prepared", "Approved", "Vendor Name"};
  data.append(header);

  qDebug() << "Header: Part Name | Part No | PURCHASE | Department | Prepared | Approved | Vendor";

  for (int i = 1; i < rows; ++i) {
    QVector<QVariant> row(7);
    data.append(row);
  }

  m_model->setExcelData(data);
  m_currentFile = "";
  setUnsavedChanges(false);

  emit currentFileChanged();

  qDebug() << "✓ Purchase file created successfully (7 columns - Excel .xlsx)";
  qDebug() << "💡 Use this to record purchases, then merge with Stock file";
  qDebug() << "========================================";
}

QString ExcelHandler::getFileName() const
{
  if (m_currentFile.isEmpty()) {
    return "Untitled";
  }
  return QFileInfo(m_currentFile).fileName();
}

QString ExcelHandler::getFileType() const
{
  // Check column 2 (index 2) header to determine file type
  QVariant header = m_model->getData(0, 2);
  QString headerText = header.toString().trimmed().toLower();

  if (headerText == "purchase") {
    return "purchase";
  } else {
    return "stock";  // default to stock
  }
}

bool ExcelHandler::loadExcel(const QString &filePath)
{
  QString cleanPath = cleanFilePath(filePath);

  qDebug() << "========================================";
  qDebug() << "Loading Excel file:" << cleanPath;

  QFileInfo fileInfo(cleanPath);
  if (!fileInfo.exists()) {
    emit errorOccurred("File does not exist: " + cleanPath);
    return false;
  }

  // ✅ CHECK IF IT'S AN EXCEL FILE
  QString suffix = fileInfo.suffix().toLower();
  if (suffix != "xlsx" && suffix != "xls") {
    QString error = "❌ Invalid file type!\n\n"
                    "Expected: Excel file (.xlsx or .xls)\n"
                    "Got: ." + suffix + " file\n\n"
                               "💡 Please select an Excel file (.xlsx)\n"
                               "💡 Use '📦 Create Stock' or '🛒 Create Purchase' to make new files";
    qDebug() << "ERROR:" << error;
    emit errorOccurred(error);

    // Clear the invalid permanent file
    if (cleanPath == m_permanentFile) {
      m_permanentFile = "";
      savePermanentFileSettings();
      emit permanentFileChanged();
    }

    return false;
  }

  QXlsx::Document xlsx(cleanPath);
  if (!xlsx.load()) {
    emit errorOccurred("Failed to load Excel file");
    return false;
  }

  QXlsx::Worksheet *sheet = xlsx.currentWorksheet();
  if (!sheet) {
    emit errorOccurred("No worksheet found");
    return false;
  }

  QXlsx::CellRange range = sheet->dimension();

  qDebug() << "📋 Raw Excel range:" << range.firstRow() << "to" << range.lastRow()
           << ", columns" << range.firstColumn() << "to" << range.lastColumn();

  // Handle invalid ranges from Google Sheets
  int startRow = range.firstRow();
  int endRow = range.lastRow();
  int startCol = range.firstColumn();
  int endCol = range.lastColumn();

  // Fix negative or invalid values (Google Sheets issue)
  if (startRow < 1) startRow = 1;
  if (startCol < 1) startCol = 1;
  if (endRow < startRow) endRow = 1000; // Default max
  if (endCol < startCol) endCol = 26; // Default to column Z

  qDebug() << "📊 Adjusted range:" << startRow << "to" << endRow
           << ", columns" << startCol << "to" << endCol;

  QVector<QVector<QVariant>> data;
  int consecutiveEmptyRows = 0;
  const int MAX_CONSECUTIVE_EMPTY = 5;

  // Read data row by row, checking actual cell content
  for (int row = startRow; row <= endRow; ++row) {
    QVector<QVariant> rowData;
    bool rowIsEmpty = true;
    int actualColumns = 0;

    // Try to read up to 26 columns (A-Z) or until we find the data
    int maxColToCheck = qMin(endCol, 26);

    for (int col = startCol; col <= maxColToCheck; ++col) {
      auto cell = sheet->cellAt(row, col);
      QVariant cellValue;

      if (cell && cell->value().isValid()) {
        cellValue = cell->value();
        // Check if cell has actual data
        QString strValue = cellValue.toString().trimmed();
        if (!strValue.isEmpty()) {
          rowIsEmpty = false;
          actualColumns = qMax(actualColumns, col - startCol + 1);
        }
      }

      rowData.append(cellValue);
    }

    // For first row (header), determine actual column count
    if (row == startRow && !rowIsEmpty) {
      qDebug() << "✓ Found header with" << actualColumns << "columns";
      // Trim rowData to actual columns
      while (rowData.size() > actualColumns) {
        rowData.removeLast();
      }
    }

    // Skip completely empty rows after header
    if (rowIsEmpty && row > startRow) {
      consecutiveEmptyRows++;
      if (consecutiveEmptyRows >= MAX_CONSECUTIVE_EMPTY) {
        qDebug() << "⏹ Stopped at row" << row << "- found" << MAX_CONSECUTIVE_EMPTY << "consecutive empty rows";
        break;
      }
      continue;
    } else if (!rowIsEmpty) {
      consecutiveEmptyRows = 0;

      // Match column count with header
      if (row > startRow && !data.isEmpty()) {
        int headerCols = data[0].size();
        while (rowData.size() > headerCols) {
          rowData.removeLast();
        }
        while (rowData.size() < headerCols) {
          rowData.append(QVariant());
        }
      }

      data.append(rowData);
    }
  }

  // Ensure all rows have the same number of columns
  if (!data.isEmpty()) {
    int maxCols = data[0].size(); // Use header column count

    qDebug() << "📏 Normalizing to" << maxCols << "columns";

    for (auto &row : data) {
      while (row.size() < maxCols) {
        row.append(QVariant());
      }
      while (row.size() > maxCols) {
        row.removeLast();
      }
    }
  }

  if (data.isEmpty()) {
    emit errorOccurred("No data found in Excel file. The file may be empty or corrupted.");
    return false;
  }

  m_model->setExcelData(data);
  m_currentFile = cleanPath;
  setUnsavedChanges(false);

  emit currentFileChanged();
  emit fileLoaded(fileInfo.fileName());

  qDebug() << "✓ Loaded:" << data.size() << "rows x" << (data.isEmpty() ? 0 : data[0].size()) << "columns";
  qDebug() << "File type:" << getFileType();
  qDebug() << "========================================";

  return true;
}

bool ExcelHandler::saveExcel(const QString &filePath)
{
  QString savePath = filePath.isEmpty() ? m_currentFile : cleanFilePath(filePath);

  if (savePath.isEmpty()) {
    emit errorOccurred("No file path specified");
    return false;
  }

  // Add .xlsx extension if not present
  if (!savePath.endsWith(".xlsx", Qt::CaseInsensitive) && !savePath.endsWith(".xls", Qt::CaseInsensitive)) {
    savePath += ".xlsx";
  }

  qDebug() << "========================================";
  qDebug() << "Saving to Excel:" << savePath;

  QXlsx::Document xlsx;
  QVector<QVector<QVariant>> data = m_model->getExcelData();

  for (int row = 0; row < data.size(); ++row) {
    for (int col = 0; col < data[row].size(); ++col) {
      xlsx.write(row + 1, col + 1, data[row][col]);
    }
  }

  if (!xlsx.saveAs(savePath)) {
    emit errorOccurred("Failed to save file");
    return false;
  }

  m_currentFile = savePath;
  setUnsavedChanges(false);

  emit currentFileChanged();
  emit fileSaved(QFileInfo(savePath).fileName());

  qDebug() << "✓ Saved successfully";
  qDebug() << "File size:" << QFileInfo(savePath).size() << "bytes";
  qDebug() << "========================================";

  return true;
}

bool ExcelHandler::validateFileStructure(const QString &filePath)
{
  QString cleanPath = cleanFilePath(filePath);

  qDebug() << "========================================";
  qDebug() << "🔍 Validating file structure:" << cleanPath;

  QXlsx::Document xlsx(cleanPath);
  if (!xlsx.load()) {
    qDebug() << "❌ Failed to load file";
    return false;
  }

  QXlsx::Worksheet *sheet = xlsx.currentWorksheet();
  if (!sheet) {
    qDebug() << "❌ No worksheet found";
    return false;
  }

  // Check columns structure (7 columns)
  qDebug() << "Checking headers:";
  for (int col = 1; col <= 7; ++col) {
    auto cell = sheet->cellAt(1, col);
    QString header = cell ? cell->value().toString().trimmed() : "";
    qDebug() << "  Column" << col << ":" << header;
  }

  // Column 3 should be "Purchase" for merge files
  auto col3Cell = sheet->cellAt(1, 3);
  QString col3Header = col3Cell ? col3Cell->value().toString().trimmed() : "";

  qDebug() << "";
  qDebug() << "Column 3 header:" << col3Header;

  if (col3Header.toLower() == "purchase") {
    qDebug() << "✓ Valid PURCHASE file for merging";
    qDebug() << "========================================";
    return true;
  } else if (col3Header.toLower() == "stock") {
    qDebug() << "❌ This is a STOCK file, not a Purchase file!";
    qDebug() << "💡 You can only merge Purchase files into Stock files";
    qDebug() << "========================================";
    return false;
  } else {
    qDebug() << "❌ Invalid file structure";
    qDebug() << "Column 3 must be 'Purchase' (found: '" << col3Header << "')";
    qDebug() << "========================================";
    return false;
  }
}

void ExcelHandler::addNewItem(const QString &partName, const QString &category,
                              int quantity, double unitPrice)
{
  Q_UNUSED(unitPrice)

  qDebug() << "Adding item:" << partName;

  int existingRow = findPartByName(partName);

  if (existingRow != -1) {
    int currentStock = m_model->getData(existingRow, 2).toInt();  // Column 2 = Stock
    m_model->setDataAt(existingRow, 2, currentStock + quantity);
    qDebug() << "  Updated existing - new stock:" << (currentStock + quantity);
  } else {
    m_model->addRow();
    int newRow = m_model->rowCount() - 1;

    // Column mapping: 0=Part Name, 1=Part No, 2=Stock, 3=Department, ...
    m_model->setDataAt(newRow, 0, partName);                      // Part Name
    m_model->setDataAt(newRow, 1, "PN-" + QString::number(newRow)); // Part No
    m_model->setDataAt(newRow, 2, quantity);                      // Stock
    m_model->setDataAt(newRow, 3, category);                      // Department

    qDebug() << "  Added new row:" << newRow;
  }
}

int ExcelHandler::getNextSerialNumber() const
{
  int maxNo = 0;
  int rows = m_model->rowCount();

  for (int row = 1; row < rows; ++row) {
    int no = m_model->getData(row, 0).toInt();
    if (no > maxNo) {
      maxNo = no;
    }
  }

  return maxNo + 1;
}

void ExcelHandler::onModelDataChanged()
{
  setUnsavedChanges(true);
}

void ExcelHandler::setUnsavedChanges(bool changed)
{
  if (m_hasUnsavedChanges != changed) {
    m_hasUnsavedChanges = changed;
    emit unsavedChangesChanged();
  }
}

QString ExcelHandler::cleanFilePath(const QString &path)
{
  QString cleanPath = path;

  if (cleanPath.startsWith("file:///")) {
    cleanPath = cleanPath.mid(8);
  } else if (cleanPath.startsWith("file://")) {
    cleanPath = cleanPath.mid(7);
  }

#ifdef Q_OS_LINUX
  if (!cleanPath.isEmpty() && !cleanPath.startsWith('/')) {
    cleanPath = "/" + cleanPath;
  }
#endif

  return cleanPath;
}
// Cloud Sync Implementation - Add to end of excelhandler.cpp

// Initialize cloud settings in constructor
void ExcelHandler::loadCloudSettings()
{
  QSettings settings("EinsteinRobotics", "StockManager");
  m_cloudFolder = settings.value("cloudFolder", "").toString();
  m_syncEnabled = settings.value("syncEnabled", false).toBool();
  m_currentUser = settings.value("currentUser", "User").toString();
  m_userRole = settings.value("userRole", "editor").toString();
  m_syncStatus = "offline";
  m_lastSyncTime = settings.value("lastSyncTime", "Never").toString();

  if (!m_cloudFolder.isEmpty() && QDir(m_cloudFolder).exists()) {
    m_syncStatus = "synced";
    qDebug() << "✓ Cloud folder loaded:" << m_cloudFolder;
  }

  // Emit signals so QML updates
  emit cloudFolderChanged();
  emit syncEnabledChanged();
  emit currentUserChanged();
  emit userRoleChanged();
  emit lastSyncTimeChanged();
  emit syncStatusChanged();
}

void ExcelHandler::saveCloudSettings()
{
  QSettings settings("EinsteinRobotics", "StockManager");
  settings.setValue("cloudFolder", m_cloudFolder);
  settings.setValue("syncEnabled", m_syncEnabled);
  settings.setValue("currentUser", m_currentUser);
  settings.setValue("userRole", m_userRole);
  settings.setValue("lastSyncTime", m_lastSyncTime);
  qDebug() << "✓ Cloud settings saved";
}

void ExcelHandler::setCloudFolder(const QString &folder)
{
  QString cleanPath = cleanFilePath(folder);

  QDir dir(cleanPath);
  if (!dir.exists()) {
    emit errorOccurred("Cloud folder does not exist: " + cleanPath);
    return;
  }

  m_cloudFolder = cleanPath;
  saveCloudSettings();
  emit cloudFolderChanged();

  qDebug() << "✓ Cloud folder set:" << m_cloudFolder;
}

void ExcelHandler::setSyncEnabled(bool enabled)
{
  if (m_syncEnabled != enabled) {
    m_syncEnabled = enabled;
    saveCloudSettings();
    emit syncEnabledChanged();
    qDebug() << "✓ Sync enabled:" << enabled;
  }
}

void ExcelHandler::setCurrentUser(const QString &username)
{
  if (m_currentUser != username) {
    m_currentUser = username;
    saveCloudSettings();
    emit currentUserChanged();
    qDebug() << "✓ Current user:" << username;
  }
}

void ExcelHandler::setUserRole(const QString &role)
{
  if (m_userRole != role) {
    m_userRole = role;
    saveCloudSettings();
    emit userRoleChanged();
    qDebug() << "✓ User role:" << role;
  }
}

void ExcelHandler::updateSyncStatus(const QString &status)
{
  if (m_syncStatus != status) {
    m_syncStatus = status;
    emit syncStatusChanged();
  }
}

bool ExcelHandler::canEdit() const
{
  return m_userRole == "owner" || m_userRole == "editor";
}

QString ExcelHandler::getCloudFilePath() const
{
  if (m_cloudFolder.isEmpty() || m_currentFile.isEmpty()) {
    return "";
  }

  QFileInfo fileInfo(m_currentFile);
  return m_cloudFolder + "/" + fileInfo.fileName();
}

bool ExcelHandler::isFileLocked(const QString &filePath) const
{
  QString lockFile = filePath + ".lock";

  if (!QFile::exists(lockFile)) {
    return false;
  }

  // Check if lock is stale (older than 5 minutes)
  QFileInfo lockInfo(lockFile);
  QDateTime lockTime = lockInfo.lastModified();
  QDateTime now = QDateTime::currentDateTime();

  if (lockTime.secsTo(now) > 300) { // 5 minutes
    qDebug() << "⚠ Found stale lock file, ignoring";
    return false;
  }

  // Read who locked it
  QFile file(lockFile);
  if (file.open(QIODevice::ReadOnly)) {
    QString lockOwner = file.readAll().trimmed();
    file.close();

    if (lockOwner != m_currentUser) {
      qDebug() << "🔒 File locked by:" << lockOwner;
      return true;
    }
  }

  return false;
}

bool ExcelHandler::lockFile(const QString &filePath)
{
  QString lockFile = filePath + ".lock";

  if (isFileLocked(filePath)) {
    return false;
  }

  QFile file(lockFile);
  if (file.open(QIODevice::WriteOnly)) {
    file.write(m_currentUser.toUtf8());
    file.close();
    qDebug() << "🔒 File locked by:" << m_currentUser;
    return true;
  }

  return false;
}

bool ExcelHandler::unlockFile(const QString &filePath)
{
  QString lockFile = filePath + ".lock";

  if (QFile::exists(lockFile)) {
    QFile::remove(lockFile);
    qDebug() << "🔓 File unlocked";
    return true;
  }

  return false;
}

bool ExcelHandler::syncToCloud()
{
  if (m_cloudFolder.isEmpty()) {
    emit errorOccurred("No cloud folder configured. Please set cloud folder first.");
    return false;
  }

  if (m_currentFile.isEmpty()) {
    emit errorOccurred("No file loaded. Please open or create a file first.");
    return false;
  }

  if (!canEdit()) {
    emit errorOccurred("You don't have permission to upload (Role: " + m_userRole + ")");
    return false;
  }

  qDebug() << "========================================";
  qDebug() << "☁️ Syncing TO cloud...";
  qDebug() << "Current file:" << m_currentFile;

  updateSyncStatus("syncing");

  QString cloudFilePath = getCloudFilePath();
  qDebug() << "Cloud file path:" << cloudFilePath;

  // Check if current file is already the cloud file
  if (QFileInfo(m_currentFile).canonicalFilePath() == QFileInfo(cloudFilePath).canonicalFilePath()) {
    qDebug() << "✓ Current file is already in cloud, just saving...";

    // Just save the file (it's already in the cloud location)
    if (saveExcel(m_currentFile)) {
      m_lastSyncTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
      saveCloudSettings();
      emit lastSyncTimeChanged();
      updateSyncStatus("synced");
      emit syncCompleted(true);
      qDebug() << "✓ File saved in cloud location";
      qDebug() << "========================================";
      return true;
    } else {
      emit errorOccurred("Failed to save file");
      updateSyncStatus("offline");
      return false;
    }
  }

  // Check if file is locked by another user
  if (isFileLocked(cloudFilePath)) {
    emit errorOccurred("File is being edited by another user. Please try again later.");
    updateSyncStatus("conflict");
    return false;
  }

  // Lock the file
  lockFile(cloudFilePath);

  // Save current file first
  if (!saveExcel(m_currentFile)) {
    unlockFile(cloudFilePath);
    emit errorOccurred("Failed to save local file");
    updateSyncStatus("synced");
    return false;
  }

  // Copy to cloud
  if (QFile::exists(cloudFilePath)) {
    if (!QFile::remove(cloudFilePath)) {
      qDebug() << "⚠ Could not remove old cloud file";
    }
  }

  if (QFile::copy(m_currentFile, cloudFilePath)) {
    m_lastSyncTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    saveCloudSettings();
    emit lastSyncTimeChanged();

    updateSyncStatus("synced");
    emit syncCompleted(true);

    qDebug() << "✓ Synced to cloud:" << cloudFilePath;
    qDebug() << "========================================";

    // Unlock after a delay (1 second) to prevent conflicts
    QTimer::singleShot(1000, [this, cloudFilePath]() {
      unlockFile(cloudFilePath);
    });

    return true;
  } else {
    unlockFile(cloudFilePath);
    qDebug() << "❌ Failed to copy" << m_currentFile << "to" << cloudFilePath;
    emit errorOccurred("Failed to upload to cloud folder. Check permissions.");
    updateSyncStatus("offline");
    return false;
  }
}

bool ExcelHandler::syncFromCloud()
{
  if (m_cloudFolder.isEmpty()) {
    emit errorOccurred("No cloud folder configured");
    return false;
  }

  qDebug() << "========================================";
  qDebug() << "☁️ Syncing FROM cloud...";

  updateSyncStatus("syncing");

  QString cloudFilePath = getCloudFilePath();

  if (!QFile::exists(cloudFilePath)) {
    emit errorOccurred("No file found in cloud folder");
    updateSyncStatus("offline");
    return false;
  }

  // Check if file is locked
  if (isFileLocked(cloudFilePath)) {
    emit errorOccurred("File is being edited by another user");
    updateSyncStatus("conflict");
    return false;
  }

  // Remember the original current file path
  QString originalFile = m_currentFile;

  // Load from cloud
  if (loadExcel(cloudFilePath)) {
    // If we have a permanent file, copy cloud file to it
    if (!m_permanentFile.isEmpty()) {
      // Copy cloud file to permanent file location
      QFile::remove(m_permanentFile);
      if (QFile::copy(cloudFilePath, m_permanentFile)) {
        m_currentFile = m_permanentFile;
        qDebug() << "✓ Copied cloud file to permanent location";
      } else {
        // If copy fails, just keep the cloud file as current
        m_currentFile = cloudFilePath;
        qDebug() << "⚠ Could not copy to permanent location, using cloud file";
      }
    } else if (!originalFile.isEmpty()) {
      // If no permanent file but we had a current file, try to copy there
      QFile::remove(originalFile);
      if (QFile::copy(cloudFilePath, originalFile)) {
        m_currentFile = originalFile;
        qDebug() << "✓ Copied cloud file to original location";
      } else {
        m_currentFile = cloudFilePath;
      }
    } else {
      // No permanent file and no current file, just use cloud file
      m_currentFile = cloudFilePath;
    }

    m_lastSyncTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    saveCloudSettings();
    emit lastSyncTimeChanged();
    emit currentFileChanged();

    updateSyncStatus("synced");
    emit syncCompleted(true);

    qDebug() << "✓ Synced from cloud";
    qDebug() << "Current file now:" << m_currentFile;
    qDebug() << "========================================";
    return true;
  } else {
    updateSyncStatus("offline");
    return false;
  }
}

bool ExcelHandler::checkForUpdates()
{
  if (m_cloudFolder.isEmpty() || m_currentFile.isEmpty()) {
    return false;
  }

  QString cloudFilePath = getCloudFilePath();

  if (!QFile::exists(cloudFilePath)) {
    return false;
  }

  QFileInfo localFile(m_currentFile);
  QFileInfo cloudFile(cloudFilePath);

  // Check if cloud file is newer
  if (cloudFile.lastModified() > localFile.lastModified()) {
    qDebug() << "⚠ Cloud file is newer!";
    emit conflictDetected("Cloud file has been updated by another user");
    return true;
  }

  return false;
}
