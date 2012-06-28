/****************************************************************************
** Meta object code from reading C++ file 'imgfilemodel.h'
**
** Created: Mon Jun 18 21:05:44 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "imgfilemodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imgfilemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImgFileModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      26,   13,   13,   13, 0x0a,
      50,   40,   13,   13, 0x0a,
      78,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ImgFileModel[] = {
    "ImgFileModel\0\0selectAll()\0unSelectAll()\0"
    "indexlist\0removeFile(QModelIndexList)\0"
    "removeAll()\0"
};

void ImgFileModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImgFileModel *_t = static_cast<ImgFileModel *>(_o);
        switch (_id) {
        case 0: _t->selectAll(); break;
        case 1: _t->unSelectAll(); break;
        case 2: _t->removeFile((*reinterpret_cast< QModelIndexList(*)>(_a[1]))); break;
        case 3: _t->removeAll(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ImgFileModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ImgFileModel::staticMetaObject = {
    { &QAbstractTableModel::staticMetaObject, qt_meta_stringdata_ImgFileModel,
      qt_meta_data_ImgFileModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImgFileModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImgFileModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImgFileModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImgFileModel))
        return static_cast<void*>(const_cast< ImgFileModel*>(this));
    return QAbstractTableModel::qt_metacast(_clname);
}

int ImgFileModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
