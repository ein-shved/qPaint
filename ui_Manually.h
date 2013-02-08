/********************************************************************************
** Form generated from reading UI file 'Manually.ui'
**
** Created: Tue Nov 20 15:48:13 2012
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANUALLY_H
#define UI_MANUALLY_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ManuallyTable
{
public:
    QDialogButtonBox *buttonBox;
    QTableWidget *table;
    QLabel *label;

    void setupUi(QDialog *ManuallyTable)
    {
        if (ManuallyTable->objectName().isEmpty())
            ManuallyTable->setObjectName(QString::fromUtf8("ManuallyTable"));
        ManuallyTable->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ManuallyTable->sizePolicy().hasHeightForWidth());
        ManuallyTable->setSizePolicy(sizePolicy);
        ManuallyTable->setSizeGripEnabled(false);
        buttonBox = new QDialogButtonBox(ManuallyTable);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(50, 250, 341, 32));
        buttonBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        table = new QTableWidget(ManuallyTable);
        table->setObjectName(QString::fromUtf8("table"));
        table->setGeometry(QRect(10, 30, 381, 211));
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table->setShowGrid(true);
        table->setGridStyle(Qt::NoPen);
        table->setWordWrap(false);
        table->setCornerButtonEnabled(false);
        table->setRowCount(0);
        table->setColumnCount(0);
        table->horizontalHeader()->setVisible(false);
        table->horizontalHeader()->setHighlightSections(false);
        table->verticalHeader()->setVisible(false);
        table->verticalHeader()->setHighlightSections(false);
        label = new QLabel(ManuallyTable);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 191, 16));
        table->raise();
        label->raise();
        buttonBox->raise();

        retranslateUi(ManuallyTable);
        QObject::connect(buttonBox, SIGNAL(accepted()), ManuallyTable, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ManuallyTable, SLOT(reject()));

        QMetaObject::connectSlotsByName(ManuallyTable);
    } // setupUi

    void retranslateUi(QDialog *ManuallyTable)
    {
        ManuallyTable->setWindowTitle(QApplication::translate("ManuallyTable", "Filter Matrix", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ManuallyTable", "Input filter matrix", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ManuallyTable: public Ui_ManuallyTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANUALLY_H
