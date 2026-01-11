#ifndef EXCELHANDLER_H
#define EXCELHANDLER_H

#include <QObject>
#include <QAbstractTableModel>
#include <QVariant>
#include <QVector>
#include <QDebug>
#include <QUrl>
#include <QFileInfo>
#include <QSettings>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QDesktopServices>
#include <QDateTime>
#include <QSet>
#include <QTimer>
#include <xlsxdocument.h>
#include <xlsxworksheet.h>

class ExcelTableModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  explicit ExcelTableModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QHash<int, QByteArray> roleNames() const override;

  void setExcelData(const QVector<QVector<QVariant>> &data);
  QVector<QVector<QVariant>> getExcelData() const;

  Q_INVOKABLE QVariant getData(int row, int column) const;
  Q_INVOKABLE bool setDataAt(int row, int column, const QVariant &value);
  Q_INVOKABLE void addRow();
  Q_INVOKABLE void addColumn();
  Q_INVOKABLE void clear();

private:
  QVector<QVector<QVariant>> m_data;
};

class ExcelHandler : public QObject
{
  Q_OBJECT
  Q_PROPERTY(ExcelTableModel* model READ model CONSTANT)
  Q_PROPERTY(QString currentFile READ currentFile NOTIFY currentFileChanged)
  Q_PROPERTY(bool hasUnsavedChanges READ hasUnsavedChanges NOTIFY unsavedChangesChanged)
  Q_PROPERTY(QString permanentFile READ permanentFile NOTIFY permanentFileChanged)

  // Cloud Sync Properties
  Q_PROPERTY(QString cloudFolder READ cloudFolder WRITE setCloudFolder NOTIFY cloudFolderChanged)
  Q_PROPERTY(bool syncEnabled READ syncEnabled WRITE setSyncEnabled NOTIFY syncEnabledChanged)
  Q_PROPERTY(QString lastSyncTime READ lastSyncTime NOTIFY lastSyncTimeChanged)
  Q_PROPERTY(QString syncStatus READ syncStatus NOTIFY syncStatusChanged)
  Q_PROPERTY(QString currentUser READ currentUser WRITE setCurrentUser NOTIFY currentUserChanged)
  Q_PROPERTY(QString userRole READ userRole WRITE setUserRole NOTIFY userRoleChanged)

public:
  explicit ExcelHandler(QObject *parent = nullptr);

  ExcelTableModel* model() const { return m_model; }
  QString currentFile() const { return m_currentFile; }
  bool hasUnsavedChanges() const { return m_hasUnsavedChanges; }
  QString permanentFile() const { return m_permanentFile; }

  Q_INVOKABLE void createNew(int rows = 10, int cols = 10);
  Q_INVOKABLE void createStockFile(int rows = 15);
  Q_INVOKABLE void createPurchaseFile(int rows = 15);
  Q_INVOKABLE QString getFileName() const;
  Q_INVOKABLE QString getFileType() const;
  Q_INVOKABLE bool loadExcel(const QString &filePath);
  Q_INVOKABLE bool saveExcel(const QString &filePath = QString());

  // Permanent file management
  Q_INVOKABLE bool setPermanentFile(const QString &filePath);
  Q_INVOKABLE bool loadPermanentFile();
  Q_INVOKABLE bool saveToPermanent();
  Q_INVOKABLE QString getSavedPermanentPath();
  Q_INVOKABLE bool hasSavedPermanentFile();

  // File merging with smart logic
  Q_INVOKABLE bool appendFromFile(const QString &filePath);
  Q_INVOKABLE bool validateFileStructure(const QString &filePath);

  // Search functionality
  Q_INVOKABLE int searchPartName(const QString &partName);
  Q_INVOKABLE QVariantList searchAllMatches(const QString &searchText);

  // File upload management
  Q_INVOKABLE bool uploadFileForPart(int row, const QString &filePath);
  Q_INVOKABLE QString getUploadedFilePath(int row);
  Q_INVOKABLE bool openUploadedFile(int row);
  Q_INVOKABLE bool hasUploadedFile(int row);

  // Stock management
  Q_INVOKABLE void addNewItem(const QString &partName,
                              const QString &category,
                              int quantity,
                              double unitPrice);
  Q_INVOKABLE int getNextSerialNumber() const;

  // Cloud Sync Methods
  Q_INVOKABLE bool syncToCloud();
  Q_INVOKABLE bool syncFromCloud();
  Q_INVOKABLE bool checkForUpdates();
  Q_INVOKABLE QString getCloudFilePath() const;
  Q_INVOKABLE bool canEdit() const;
  Q_INVOKABLE void setCloudFolder(const QString &folder);
  Q_INVOKABLE void setCurrentUser(const QString &username);
  Q_INVOKABLE void setUserRole(const QString &role);
  Q_INVOKABLE void setSyncEnabled(bool enabled);

  // Getters for cloud properties
  QString cloudFolder() const { return m_cloudFolder; }
  bool syncEnabled() const { return m_syncEnabled; }
  QString lastSyncTime() const { return m_lastSyncTime; }
  QString syncStatus() const { return m_syncStatus; }
  QString currentUser() const { return m_currentUser; }
  QString userRole() const { return m_userRole; }

signals:
  void currentFileChanged();
  void unsavedChangesChanged();
  void permanentFileChanged();
  void errorOccurred(const QString &error);
  void fileLoaded(const QString &fileName);
  void fileSaved(const QString &fileName);
  void fileMerged(const QString &fileName, int rowsAdded, int rowsUpdated);
  void searchResultFound(int row);

  // Cloud sync signals
  void cloudFolderChanged();
  void syncEnabledChanged();
  void lastSyncTimeChanged();
  void syncStatusChanged();
  void currentUserChanged();
  void userRoleChanged();
  void syncCompleted(bool success);
  void conflictDetected(const QString &message);

private slots:
  void onModelDataChanged();

private:
  ExcelTableModel *m_model;
  QString m_currentFile;
  QString m_permanentFile;
  bool m_hasUnsavedChanges;
  QString m_uploadsDir;

  // Cloud sync members
  QString m_cloudFolder;
  bool m_syncEnabled;
  QString m_lastSyncTime;
  QString m_syncStatus;
  QString m_currentUser;
  QString m_userRole;

  void setUnsavedChanges(bool changed);
  QString cleanFilePath(const QString &path);
  void recalculateSerialNumbers();
  void savePermanentFileSettings();
  void loadPermanentFileSettings();
  void initializeUploadsDirectory();
  int findPartByName(const QString &partName);
  bool updateExistingPart(int row, const QVector<QVariant> &newData);

  // Cloud sync helpers
  void updateSyncStatus(const QString &status);
  void saveCloudSettings();
  void loadCloudSettings();
  bool isFileLocked(const QString &filePath) const;
  bool lockFile(const QString &filePath);
  bool unlockFile(const QString &filePath);
};

#endif // EXCELHANDLER_H
