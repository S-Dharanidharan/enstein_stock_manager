/****************************************************************************
** Meta object code from reading C++ file 'excelhandler.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../excelhandler.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'excelhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN15ExcelTableModelE_t {};
} // unnamed namespace

template <> constexpr inline auto ExcelTableModel::qt_create_metaobjectdata<qt_meta_tag_ZN15ExcelTableModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ExcelTableModel",
        "getData",
        "QVariant",
        "",
        "row",
        "column",
        "setDataAt",
        "value",
        "addRow",
        "addColumn",
        "clear"
    };

    QtMocHelpers::UintData qt_methods {
        // Method 'getData'
        QtMocHelpers::MethodData<QVariant(int, int) const>(1, 3, QMC::AccessPublic, 0x80000000 | 2, {{
            { QMetaType::Int, 4 }, { QMetaType::Int, 5 },
        }}),
        // Method 'setDataAt'
        QtMocHelpers::MethodData<bool(int, int, const QVariant &)>(6, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 4 }, { QMetaType::Int, 5 }, { 0x80000000 | 2, 7 },
        }}),
        // Method 'addRow'
        QtMocHelpers::MethodData<void()>(8, 3, QMC::AccessPublic, QMetaType::Void),
        // Method 'addColumn'
        QtMocHelpers::MethodData<void()>(9, 3, QMC::AccessPublic, QMetaType::Void),
        // Method 'clear'
        QtMocHelpers::MethodData<void()>(10, 3, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ExcelTableModel, qt_meta_tag_ZN15ExcelTableModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ExcelTableModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractTableModel::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15ExcelTableModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15ExcelTableModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15ExcelTableModelE_t>.metaTypes,
    nullptr
} };

void ExcelTableModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ExcelTableModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { QVariant _r = _t->getData((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QVariant*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->setDataAt((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QVariant>>(_a[3])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->addRow(); break;
        case 3: _t->addColumn(); break;
        case 4: _t->clear(); break;
        default: ;
        }
    }
}

const QMetaObject *ExcelTableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExcelTableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15ExcelTableModelE_t>.strings))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int ExcelTableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN12ExcelHandlerE_t {};
} // unnamed namespace

template <> constexpr inline auto ExcelHandler::qt_create_metaobjectdata<qt_meta_tag_ZN12ExcelHandlerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ExcelHandler",
        "currentFileChanged",
        "",
        "unsavedChangesChanged",
        "permanentFileChanged",
        "errorOccurred",
        "error",
        "fileLoaded",
        "fileName",
        "fileSaved",
        "fileMerged",
        "rowsAdded",
        "rowsUpdated",
        "searchResultFound",
        "row",
        "cloudFolderChanged",
        "syncEnabledChanged",
        "lastSyncTimeChanged",
        "syncStatusChanged",
        "currentUserChanged",
        "userRoleChanged",
        "syncCompleted",
        "success",
        "conflictDetected",
        "message",
        "onModelDataChanged",
        "createNew",
        "rows",
        "cols",
        "createStockFile",
        "createPurchaseFile",
        "getFileName",
        "getFileType",
        "loadExcel",
        "filePath",
        "saveExcel",
        "setPermanentFile",
        "loadPermanentFile",
        "saveToPermanent",
        "getSavedPermanentPath",
        "hasSavedPermanentFile",
        "appendFromFile",
        "validateFileStructure",
        "searchPartName",
        "partName",
        "searchAllMatches",
        "QVariantList",
        "searchText",
        "uploadFileForPart",
        "getUploadedFilePath",
        "openUploadedFile",
        "hasUploadedFile",
        "addNewItem",
        "category",
        "quantity",
        "unitPrice",
        "getNextSerialNumber",
        "syncToCloud",
        "syncFromCloud",
        "checkForUpdates",
        "getCloudFilePath",
        "canEdit",
        "setCloudFolder",
        "folder",
        "setCurrentUser",
        "username",
        "setUserRole",
        "role",
        "setSyncEnabled",
        "enabled",
        "model",
        "ExcelTableModel*",
        "currentFile",
        "hasUnsavedChanges",
        "permanentFile",
        "cloudFolder",
        "syncEnabled",
        "lastSyncTime",
        "syncStatus",
        "currentUser",
        "userRole"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'currentFileChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'unsavedChangesChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'permanentFileChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'errorOccurred'
        QtMocHelpers::SignalData<void(const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'fileLoaded'
        QtMocHelpers::SignalData<void(const QString &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Signal 'fileSaved'
        QtMocHelpers::SignalData<void(const QString &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Signal 'fileMerged'
        QtMocHelpers::SignalData<void(const QString &, int, int)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 }, { QMetaType::Int, 11 }, { QMetaType::Int, 12 },
        }}),
        // Signal 'searchResultFound'
        QtMocHelpers::SignalData<void(int)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 14 },
        }}),
        // Signal 'cloudFolderChanged'
        QtMocHelpers::SignalData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'syncEnabledChanged'
        QtMocHelpers::SignalData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'lastSyncTimeChanged'
        QtMocHelpers::SignalData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'syncStatusChanged'
        QtMocHelpers::SignalData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'currentUserChanged'
        QtMocHelpers::SignalData<void()>(19, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'userRoleChanged'
        QtMocHelpers::SignalData<void()>(20, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'syncCompleted'
        QtMocHelpers::SignalData<void(bool)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 22 },
        }}),
        // Signal 'conflictDetected'
        QtMocHelpers::SignalData<void(const QString &)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 24 },
        }}),
        // Slot 'onModelDataChanged'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPrivate, QMetaType::Void),
        // Method 'createNew'
        QtMocHelpers::MethodData<void(int, int)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 27 }, { QMetaType::Int, 28 },
        }}),
        // Method 'createNew'
        QtMocHelpers::MethodData<void(int)>(26, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::Int, 27 },
        }}),
        // Method 'createNew'
        QtMocHelpers::MethodData<void()>(26, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void),
        // Method 'createStockFile'
        QtMocHelpers::MethodData<void(int)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 27 },
        }}),
        // Method 'createStockFile'
        QtMocHelpers::MethodData<void()>(29, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void),
        // Method 'createPurchaseFile'
        QtMocHelpers::MethodData<void(int)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 27 },
        }}),
        // Method 'createPurchaseFile'
        QtMocHelpers::MethodData<void()>(30, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void),
        // Method 'getFileName'
        QtMocHelpers::MethodData<QString() const>(31, 2, QMC::AccessPublic, QMetaType::QString),
        // Method 'getFileType'
        QtMocHelpers::MethodData<QString() const>(32, 2, QMC::AccessPublic, QMetaType::QString),
        // Method 'loadExcel'
        QtMocHelpers::MethodData<bool(const QString &)>(33, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 34 },
        }}),
        // Method 'saveExcel'
        QtMocHelpers::MethodData<bool(const QString &)>(35, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 34 },
        }}),
        // Method 'saveExcel'
        QtMocHelpers::MethodData<bool()>(35, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Bool),
        // Method 'setPermanentFile'
        QtMocHelpers::MethodData<bool(const QString &)>(36, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 34 },
        }}),
        // Method 'loadPermanentFile'
        QtMocHelpers::MethodData<bool()>(37, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'saveToPermanent'
        QtMocHelpers::MethodData<bool()>(38, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'getSavedPermanentPath'
        QtMocHelpers::MethodData<QString()>(39, 2, QMC::AccessPublic, QMetaType::QString),
        // Method 'hasSavedPermanentFile'
        QtMocHelpers::MethodData<bool()>(40, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'appendFromFile'
        QtMocHelpers::MethodData<bool(const QString &)>(41, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 34 },
        }}),
        // Method 'validateFileStructure'
        QtMocHelpers::MethodData<bool(const QString &)>(42, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 34 },
        }}),
        // Method 'searchPartName'
        QtMocHelpers::MethodData<int(const QString &)>(43, 2, QMC::AccessPublic, QMetaType::Int, {{
            { QMetaType::QString, 44 },
        }}),
        // Method 'searchAllMatches'
        QtMocHelpers::MethodData<QVariantList(const QString &)>(45, 2, QMC::AccessPublic, 0x80000000 | 46, {{
            { QMetaType::QString, 47 },
        }}),
        // Method 'uploadFileForPart'
        QtMocHelpers::MethodData<bool(int, const QString &)>(48, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 14 }, { QMetaType::QString, 34 },
        }}),
        // Method 'getUploadedFilePath'
        QtMocHelpers::MethodData<QString(int)>(49, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::Int, 14 },
        }}),
        // Method 'openUploadedFile'
        QtMocHelpers::MethodData<bool(int)>(50, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 14 },
        }}),
        // Method 'hasUploadedFile'
        QtMocHelpers::MethodData<bool(int)>(51, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 14 },
        }}),
        // Method 'addNewItem'
        QtMocHelpers::MethodData<void(const QString &, const QString &, int, double)>(52, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 44 }, { QMetaType::QString, 53 }, { QMetaType::Int, 54 }, { QMetaType::Double, 55 },
        }}),
        // Method 'getNextSerialNumber'
        QtMocHelpers::MethodData<int() const>(56, 2, QMC::AccessPublic, QMetaType::Int),
        // Method 'syncToCloud'
        QtMocHelpers::MethodData<bool()>(57, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'syncFromCloud'
        QtMocHelpers::MethodData<bool()>(58, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'checkForUpdates'
        QtMocHelpers::MethodData<bool()>(59, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'getCloudFilePath'
        QtMocHelpers::MethodData<QString() const>(60, 2, QMC::AccessPublic, QMetaType::QString),
        // Method 'canEdit'
        QtMocHelpers::MethodData<bool() const>(61, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'setCloudFolder'
        QtMocHelpers::MethodData<void(const QString &)>(62, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 63 },
        }}),
        // Method 'setCurrentUser'
        QtMocHelpers::MethodData<void(const QString &)>(64, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 65 },
        }}),
        // Method 'setUserRole'
        QtMocHelpers::MethodData<void(const QString &)>(66, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 67 },
        }}),
        // Method 'setSyncEnabled'
        QtMocHelpers::MethodData<void(bool)>(68, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 69 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'model'
        QtMocHelpers::PropertyData<ExcelTableModel*>(70, 0x80000000 | 71, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'currentFile'
        QtMocHelpers::PropertyData<QString>(72, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'hasUnsavedChanges'
        QtMocHelpers::PropertyData<bool>(73, QMetaType::Bool, QMC::DefaultPropertyFlags, 1),
        // property 'permanentFile'
        QtMocHelpers::PropertyData<QString>(74, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
        // property 'cloudFolder'
        QtMocHelpers::PropertyData<QString>(75, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 8),
        // property 'syncEnabled'
        QtMocHelpers::PropertyData<bool>(76, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 9),
        // property 'lastSyncTime'
        QtMocHelpers::PropertyData<QString>(77, QMetaType::QString, QMC::DefaultPropertyFlags, 10),
        // property 'syncStatus'
        QtMocHelpers::PropertyData<QString>(78, QMetaType::QString, QMC::DefaultPropertyFlags, 11),
        // property 'currentUser'
        QtMocHelpers::PropertyData<QString>(79, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 12),
        // property 'userRole'
        QtMocHelpers::PropertyData<QString>(80, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 13),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ExcelHandler, qt_meta_tag_ZN12ExcelHandlerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ExcelHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12ExcelHandlerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12ExcelHandlerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12ExcelHandlerE_t>.metaTypes,
    nullptr
} };

void ExcelHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ExcelHandler *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->currentFileChanged(); break;
        case 1: _t->unsavedChangesChanged(); break;
        case 2: _t->permanentFileChanged(); break;
        case 3: _t->errorOccurred((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->fileLoaded((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->fileSaved((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->fileMerged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3]))); break;
        case 7: _t->searchResultFound((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->cloudFolderChanged(); break;
        case 9: _t->syncEnabledChanged(); break;
        case 10: _t->lastSyncTimeChanged(); break;
        case 11: _t->syncStatusChanged(); break;
        case 12: _t->currentUserChanged(); break;
        case 13: _t->userRoleChanged(); break;
        case 14: _t->syncCompleted((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 15: _t->conflictDetected((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: _t->onModelDataChanged(); break;
        case 17: _t->createNew((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 18: _t->createNew((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 19: _t->createNew(); break;
        case 20: _t->createStockFile((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 21: _t->createStockFile(); break;
        case 22: _t->createPurchaseFile((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 23: _t->createPurchaseFile(); break;
        case 24: { QString _r = _t->getFileName();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 25: { QString _r = _t->getFileType();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 26: { bool _r = _t->loadExcel((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 27: { bool _r = _t->saveExcel((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 28: { bool _r = _t->saveExcel();
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 29: { bool _r = _t->setPermanentFile((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 30: { bool _r = _t->loadPermanentFile();
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 31: { bool _r = _t->saveToPermanent();
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 32: { QString _r = _t->getSavedPermanentPath();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 33: { bool _r = _t->hasSavedPermanentFile();
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 34: { bool _r = _t->appendFromFile((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 35: { bool _r = _t->validateFileStructure((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 36: { int _r = _t->searchPartName((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 37: { QVariantList _r = _t->searchAllMatches((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 38: { bool _r = _t->uploadFileForPart((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 39: { QString _r = _t->getUploadedFilePath((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 40: { bool _r = _t->openUploadedFile((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 41: { bool _r = _t->hasUploadedFile((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 42: _t->addNewItem((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[4]))); break;
        case 43: { int _r = _t->getNextSerialNumber();
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 44: { bool _r = _t->syncToCloud();
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 45: { bool _r = _t->syncFromCloud();
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 46: { bool _r = _t->checkForUpdates();
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 47: { QString _r = _t->getCloudFilePath();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 48: { bool _r = _t->canEdit();
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 49: _t->setCloudFolder((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 50: _t->setCurrentUser((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 51: _t->setUserRole((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 52: _t->setSyncEnabled((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ExcelHandler::*)()>(_a, &ExcelHandler::currentFileChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExcelHandler::*)()>(_a, &ExcelHandler::unsavedChangesChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExcelHandler::*)()>(_a, &ExcelHandler::permanentFileChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExcelHandler::*)(const QString & )>(_a, &ExcelHandler::errorOccurred, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExcelHandler::*)(const QString & )>(_a, &ExcelHandler::fileLoaded, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExcelHandler::*)(const QString & )>(_a, &ExcelHandler::fileSaved, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExcelHandler::*)(const QString & , int , int )>(_a, &ExcelHandler::fileMerged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExcelHandler::*)(int )>(_a, &ExcelHandler::searchResultFound, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExcelHandler::*)()>(_a, &ExcelHandler::cloudFolderChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExcelHandler::*)()>(_a, &ExcelHandler::syncEnabledChanged, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExcelHandler::*)()>(_a, &ExcelHandler::lastSyncTimeChanged, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExcelHandler::*)()>(_a, &ExcelHandler::syncStatusChanged, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExcelHandler::*)()>(_a, &ExcelHandler::currentUserChanged, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExcelHandler::*)()>(_a, &ExcelHandler::userRoleChanged, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExcelHandler::*)(bool )>(_a, &ExcelHandler::syncCompleted, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExcelHandler::*)(const QString & )>(_a, &ExcelHandler::conflictDetected, 15))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ExcelTableModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<ExcelTableModel**>(_v) = _t->model(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->currentFile(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->hasUnsavedChanges(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->permanentFile(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->cloudFolder(); break;
        case 5: *reinterpret_cast<bool*>(_v) = _t->syncEnabled(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->lastSyncTime(); break;
        case 7: *reinterpret_cast<QString*>(_v) = _t->syncStatus(); break;
        case 8: *reinterpret_cast<QString*>(_v) = _t->currentUser(); break;
        case 9: *reinterpret_cast<QString*>(_v) = _t->userRole(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 4: _t->setCloudFolder(*reinterpret_cast<QString*>(_v)); break;
        case 5: _t->setSyncEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 8: _t->setCurrentUser(*reinterpret_cast<QString*>(_v)); break;
        case 9: _t->setUserRole(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *ExcelHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExcelHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12ExcelHandlerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ExcelHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 53)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 53;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 53)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 53;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ExcelHandler::currentFileChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ExcelHandler::unsavedChangesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ExcelHandler::permanentFileChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ExcelHandler::errorOccurred(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void ExcelHandler::fileLoaded(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void ExcelHandler::fileSaved(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void ExcelHandler::fileMerged(const QString & _t1, int _t2, int _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2, _t3);
}

// SIGNAL 7
void ExcelHandler::searchResultFound(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}

// SIGNAL 8
void ExcelHandler::cloudFolderChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void ExcelHandler::syncEnabledChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void ExcelHandler::lastSyncTimeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void ExcelHandler::syncStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void ExcelHandler::currentUserChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void ExcelHandler::userRoleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void ExcelHandler::syncCompleted(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 14, nullptr, _t1);
}

// SIGNAL 15
void ExcelHandler::conflictDetected(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 15, nullptr, _t1);
}
QT_WARNING_POP
