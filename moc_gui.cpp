/****************************************************************************
** Meta object code from reading C++ file 'gui.h'
**
** Created: Tue Nov 20 15:48:33 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/GUI/gui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QFilterThread[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QFilterThread[] = {
    "QFilterThread\0\0terminate()\0"
};

const QMetaObject QFilterThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_QFilterThread,
      qt_meta_data_QFilterThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QFilterThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QFilterThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QFilterThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QFilterThread))
        return static_cast<void*>(const_cast< QFilterThread*>(this));
    return QThread::qt_metacast(_clname);
}

int QFilterThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: terminate(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_ManuallyTable[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      24,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ManuallyTable[] = {
    "ManuallyTable\0\0accept()\0reject()\0"
};

const QMetaObject ManuallyTable::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ManuallyTable,
      qt_meta_data_ManuallyTable, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ManuallyTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ManuallyTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ManuallyTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ManuallyTable))
        return static_cast<void*>(const_cast< ManuallyTable*>(this));
    return QDialog::qt_metacast(_clname);
}

int ManuallyTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: accept(); break;
        case 1: reject(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_GUI[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x08,
      14,    4,    4,    4, 0x08,
      23,    4,    4,    4, 0x08,
      32,    4,    4,    4, 0x08,
      43,    4,    4,    4, 0x08,
      53,    4,    4,    4, 0x08,
      67,    4,    4,    4, 0x08,
      87,    4,    4,    4, 0x08,
     111,    4,    4,    4, 0x08,
     125,    4,    4,    4, 0x08,
     136,    4,    4,    4, 0x08,
     149,    4,    4,    4, 0x08,
     185,    4,    4,    4, 0x08,
     226,    4,    4,    4, 0x08,
     236,    4,    4,    4, 0x08,
     246,    4,    4,    4, 0x08,
     257,    4,    4,    4, 0x08,
     270,    4,    4,    4, 0x08,
     286,    4,    4,    4, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GUI[] = {
    "GUI\0\0onExit()\0onOpen()\0onSave()\0"
    "onSaveAs()\0onAbout()\0onGrayscale()\0"
    "onHystogramLinear()\0onHystogramPerChennel()\0"
    "onGreyWorld()\0onMedian()\0onGaussian()\0"
    "onEditGaussian_TextChanged(QString)\0"
    "onEditGaussianSigma_TextChanged(QString)\0"
    "onSobel()\0onScale()\0onRotate()\0"
    "onManually()\0onManuallyRun()\0onGlass()\0"
};

const QMetaObject GUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GUI,
      qt_meta_data_GUI, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUI))
        return static_cast<void*>(const_cast< GUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onExit(); break;
        case 1: onOpen(); break;
        case 2: onSave(); break;
        case 3: onSaveAs(); break;
        case 4: onAbout(); break;
        case 5: onGrayscale(); break;
        case 6: onHystogramLinear(); break;
        case 7: onHystogramPerChennel(); break;
        case 8: onGreyWorld(); break;
        case 9: onMedian(); break;
        case 10: onGaussian(); break;
        case 11: onEditGaussian_TextChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: onEditGaussianSigma_TextChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: onSobel(); break;
        case 14: onScale(); break;
        case 15: onRotate(); break;
        case 16: onManually(); break;
        case 17: onManuallyRun(); break;
        case 18: onGlass(); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
