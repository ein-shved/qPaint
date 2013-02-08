/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created: Tue Nov 20 15:48:13 2012
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUIClass
{
public:
    QAction *mnuOpen;
    QAction *mnuSave;
    QAction *mnuSaveAs;
    QAction *action_4;
    QAction *mnuExit;
    QAction *action_7;
    QAction *action_8;
    QAction *mnuAbout;
    QAction *mnuGrayscale;
    QAction *mnuHygramLinear;
    QAction *mnuHygramChennel;
    QAction *mnuGreyWorld;
    QAction *mnuMedian;
    QAction *mnuGaussian;
    QAction *mnuSobel;
    QAction *mnuScale;
    QAction *mnuRotate;
    QAction *mnuManually;
    QAction *mnuGlass;
    QWidget *centralWidget;
    QGroupBox *gbImage;
    QPushButton *btnOpen;
    QPushButton *btnSave;
    QPushButton *btnSaveAs;
    QGroupBox *gbFilters;
    QPushButton *btnGreyWorld;
    QPushButton *btnMedian;
    QPushButton *btnGrayscale;
    QPushButton *btnHygramLinear;
    QPushButton *btnHygramChennel;
    QLineEdit *editMedian;
    QLabel *labelWarning;
    QPushButton *btnGaussian;
    QLineEdit *editGaussianSigma;
    QLineEdit *editGaussian;
    QPushButton *btnSobel;
    QPushButton *btnScale;
    QLineEdit *editScale;
    QLabel *px_label0;
    QLabel *px_label1;
    QLabel *label;
    QPushButton *btnRotate;
    QLineEdit *editRotate;
    QLabel *label_2;
    QPushButton *btnManually;
    QLineEdit *editManuallyX;
    QLineEdit *editManuallyY;
    QLabel *label_3;
    QPushButton *btnGlass;
    QFrame *line;
    QFrame *line_2;
    QGraphicsView *gvMain;
    QProgressBar *pbMain;
    QMenuBar *menuBar;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu;

    void setupUi(QMainWindow *GUIClass)
    {
        if (GUIClass->objectName().isEmpty())
            GUIClass->setObjectName(QString::fromUtf8("GUIClass"));
        GUIClass->resize(748, 531);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GUIClass->sizePolicy().hasHeightForWidth());
        GUIClass->setSizePolicy(sizePolicy);
        GUIClass->setMinimumSize(QSize(748, 531));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/GUI/Resources/mainicon.png"), QSize(), QIcon::Normal, QIcon::Off);
        GUIClass->setWindowIcon(icon);
        mnuOpen = new QAction(GUIClass);
        mnuOpen->setObjectName(QString::fromUtf8("mnuOpen"));
        mnuSave = new QAction(GUIClass);
        mnuSave->setObjectName(QString::fromUtf8("mnuSave"));
        mnuSaveAs = new QAction(GUIClass);
        mnuSaveAs->setObjectName(QString::fromUtf8("mnuSaveAs"));
        action_4 = new QAction(GUIClass);
        action_4->setObjectName(QString::fromUtf8("action_4"));
        mnuExit = new QAction(GUIClass);
        mnuExit->setObjectName(QString::fromUtf8("mnuExit"));
        action_7 = new QAction(GUIClass);
        action_7->setObjectName(QString::fromUtf8("action_7"));
        action_8 = new QAction(GUIClass);
        action_8->setObjectName(QString::fromUtf8("action_8"));
        mnuAbout = new QAction(GUIClass);
        mnuAbout->setObjectName(QString::fromUtf8("mnuAbout"));
        mnuGrayscale = new QAction(GUIClass);
        mnuGrayscale->setObjectName(QString::fromUtf8("mnuGrayscale"));
        mnuHygramLinear = new QAction(GUIClass);
        mnuHygramLinear->setObjectName(QString::fromUtf8("mnuHygramLinear"));
        mnuHygramChennel = new QAction(GUIClass);
        mnuHygramChennel->setObjectName(QString::fromUtf8("mnuHygramChennel"));
        mnuGreyWorld = new QAction(GUIClass);
        mnuGreyWorld->setObjectName(QString::fromUtf8("mnuGreyWorld"));
        mnuMedian = new QAction(GUIClass);
        mnuMedian->setObjectName(QString::fromUtf8("mnuMedian"));
        mnuGaussian = new QAction(GUIClass);
        mnuGaussian->setObjectName(QString::fromUtf8("mnuGaussian"));
        mnuSobel = new QAction(GUIClass);
        mnuSobel->setObjectName(QString::fromUtf8("mnuSobel"));
        mnuScale = new QAction(GUIClass);
        mnuScale->setObjectName(QString::fromUtf8("mnuScale"));
        mnuRotate = new QAction(GUIClass);
        mnuRotate->setObjectName(QString::fromUtf8("mnuRotate"));
        mnuManually = new QAction(GUIClass);
        mnuManually->setObjectName(QString::fromUtf8("mnuManually"));
        mnuGlass = new QAction(GUIClass);
        mnuGlass->setObjectName(QString::fromUtf8("mnuGlass"));
        centralWidget = new QWidget(GUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gbImage = new QGroupBox(centralWidget);
        gbImage->setObjectName(QString::fromUtf8("gbImage"));
        gbImage->setGeometry(QRect(10, 10, 181, 111));
        btnOpen = new QPushButton(gbImage);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));
        btnOpen->setGeometry(QRect(10, 20, 161, 23));
        btnSave = new QPushButton(gbImage);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setGeometry(QRect(10, 50, 161, 23));
        btnSaveAs = new QPushButton(gbImage);
        btnSaveAs->setObjectName(QString::fromUtf8("btnSaveAs"));
        btnSaveAs->setGeometry(QRect(10, 80, 161, 23));
        gbFilters = new QGroupBox(centralWidget);
        gbFilters->setObjectName(QString::fromUtf8("gbFilters"));
        gbFilters->setGeometry(QRect(10, 120, 180, 341));
        gbFilters->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btnGreyWorld = new QPushButton(gbFilters);
        btnGreyWorld->setObjectName(QString::fromUtf8("btnGreyWorld"));
        btnGreyWorld->setGeometry(QRect(10, 95, 160, 23));
        btnMedian = new QPushButton(gbFilters);
        btnMedian->setObjectName(QString::fromUtf8("btnMedian"));
        btnMedian->setGeometry(QRect(10, 120, 115, 23));
        btnGrayscale = new QPushButton(gbFilters);
        btnGrayscale->setObjectName(QString::fromUtf8("btnGrayscale"));
        btnGrayscale->setGeometry(QRect(10, 20, 160, 23));
        btnHygramLinear = new QPushButton(gbFilters);
        btnHygramLinear->setObjectName(QString::fromUtf8("btnHygramLinear"));
        btnHygramLinear->setGeometry(QRect(10, 45, 160, 23));
        btnHygramChennel = new QPushButton(gbFilters);
        btnHygramChennel->setObjectName(QString::fromUtf8("btnHygramChennel"));
        btnHygramChennel->setGeometry(QRect(10, 70, 160, 23));
        editMedian = new QLineEdit(gbFilters);
        editMedian->setObjectName(QString::fromUtf8("editMedian"));
        editMedian->setGeometry(QRect(125, 120, 35, 23));
        editMedian->setMaxLength(3);
        editMedian->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelWarning = new QLabel(gbFilters);
        labelWarning->setObjectName(QString::fromUtf8("labelWarning"));
        labelWarning->setEnabled(true);
        labelWarning->setGeometry(QRect(10, 320, 131, 16));
        labelWarning->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        btnGaussian = new QPushButton(gbFilters);
        btnGaussian->setObjectName(QString::fromUtf8("btnGaussian"));
        btnGaussian->setGeometry(QRect(10, 145, 70, 22));
        editGaussianSigma = new QLineEdit(gbFilters);
        editGaussianSigma->setObjectName(QString::fromUtf8("editGaussianSigma"));
        editGaussianSigma->setEnabled(false);
        editGaussianSigma->setGeometry(QRect(80, 145, 45, 23));
        editGaussianSigma->setMaxLength(4);
        editGaussianSigma->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        editGaussian = new QLineEdit(gbFilters);
        editGaussian->setObjectName(QString::fromUtf8("editGaussian"));
        editGaussian->setEnabled(true);
        editGaussian->setGeometry(QRect(125, 145, 35, 23));
        editGaussian->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btnSobel = new QPushButton(gbFilters);
        btnSobel->setObjectName(QString::fromUtf8("btnSobel"));
        btnSobel->setGeometry(QRect(10, 170, 160, 22));
        btnScale = new QPushButton(gbFilters);
        btnScale->setObjectName(QString::fromUtf8("btnScale"));
        btnScale->setGeometry(QRect(10, 260, 70, 22));
        editScale = new QLineEdit(gbFilters);
        editScale->setObjectName(QString::fromUtf8("editScale"));
        editScale->setGeometry(QRect(80, 260, 70, 23));
        editScale->setMaxLength(9);
        editScale->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        px_label0 = new QLabel(gbFilters);
        px_label0->setObjectName(QString::fromUtf8("px_label0"));
        px_label0->setGeometry(QRect(160, 125, 16, 16));
        px_label1 = new QLabel(gbFilters);
        px_label1->setObjectName(QString::fromUtf8("px_label1"));
        px_label1->setGeometry(QRect(160, 150, 16, 16));
        label = new QLabel(gbFilters);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 265, 25, 16));
        btnRotate = new QPushButton(gbFilters);
        btnRotate->setObjectName(QString::fromUtf8("btnRotate"));
        btnRotate->setGeometry(QRect(10, 235, 125, 22));
        editRotate = new QLineEdit(gbFilters);
        editRotate->setObjectName(QString::fromUtf8("editRotate"));
        editRotate->setGeometry(QRect(135, 235, 35, 23));
        editRotate->setMaxLength(4);
        label_2 = new QLabel(gbFilters);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(167, 235, 16, 16));
        btnManually = new QPushButton(gbFilters);
        btnManually->setObjectName(QString::fromUtf8("btnManually"));
        btnManually->setGeometry(QRect(10, 300, 85, 22));
        editManuallyX = new QLineEdit(gbFilters);
        editManuallyX->setObjectName(QString::fromUtf8("editManuallyX"));
        editManuallyX->setGeometry(QRect(95, 300, 35, 23));
        editManuallyX->setMaxLength(3);
        editManuallyX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        editManuallyY = new QLineEdit(gbFilters);
        editManuallyY->setObjectName(QString::fromUtf8("editManuallyY"));
        editManuallyY->setGeometry(QRect(135, 300, 35, 23));
        editManuallyY->setMaxLength(3);
        editManuallyY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(gbFilters);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(130, 305, 10, 16));
        btnGlass = new QPushButton(gbFilters);
        btnGlass->setObjectName(QString::fromUtf8("btnGlass"));
        btnGlass->setGeometry(QRect(10, 195, 160, 22));
        line = new QFrame(gbFilters);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 220, 180, 12));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(gbFilters);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(0, 285, 180, 12));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        gvMain = new QGraphicsView(centralWidget);
        gvMain->setObjectName(QString::fromUtf8("gvMain"));
        gvMain->setGeometry(QRect(200, 10, 541, 471));
        gvMain->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        pbMain = new QProgressBar(centralWidget);
        pbMain->setObjectName(QString::fromUtf8("pbMain"));
        pbMain->setGeometry(QRect(10, 490, 731, 16));
        pbMain->setValue(0);
        pbMain->setTextVisible(true);
        pbMain->setInvertedAppearance(false);
        GUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 748, 19));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        GUIClass->setMenuBar(menuBar);
        QWidget::setTabOrder(btnOpen, btnSave);
        QWidget::setTabOrder(btnSave, btnSaveAs);
        QWidget::setTabOrder(btnSaveAs, btnGrayscale);
        QWidget::setTabOrder(btnGrayscale, btnHygramLinear);
        QWidget::setTabOrder(btnHygramLinear, btnHygramChennel);
        QWidget::setTabOrder(btnHygramChennel, btnGreyWorld);
        QWidget::setTabOrder(btnGreyWorld, btnMedian);
        QWidget::setTabOrder(btnMedian, editMedian);
        QWidget::setTabOrder(editMedian, btnGaussian);
        QWidget::setTabOrder(btnGaussian, editGaussianSigma);
        QWidget::setTabOrder(editGaussianSigma, editGaussian);
        QWidget::setTabOrder(editGaussian, gvMain);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menu_2->addAction(mnuGrayscale);
        menu_2->addAction(mnuHygramLinear);
        menu_2->addAction(mnuHygramChennel);
        menu_2->addAction(mnuGreyWorld);
        menu_2->addAction(mnuMedian);
        menu_2->addAction(mnuGaussian);
        menu_2->addAction(mnuSobel);
        menu_2->addAction(mnuScale);
        menu_2->addAction(mnuRotate);
        menu_2->addAction(mnuManually);
        menu_2->addAction(mnuGlass);
        menu_3->addAction(mnuAbout);
        menu->addAction(mnuOpen);
        menu->addAction(mnuSave);
        menu->addAction(mnuSaveAs);
        menu->addSeparator();
        menu->addAction(mnuExit);

        retranslateUi(GUIClass);
        QObject::connect(editGaussianSigma, SIGNAL(textEdited(QString)), GUIClass, SLOT(onEditGaussianSigma_TextChanged(QString)));
        QObject::connect(editGaussian, SIGNAL(textEdited(QString)), GUIClass, SLOT(onEditGaussian_TextChanged(QString)));
        QObject::connect(btnGaussian, SIGNAL(clicked()), GUIClass, SLOT(onGaussian()));
        QObject::connect(editScale, SIGNAL(returnPressed()), btnScale, SLOT(click()));
        QObject::connect(editGaussian, SIGNAL(returnPressed()), btnGaussian, SLOT(click()));
        QObject::connect(editRotate, SIGNAL(returnPressed()), btnRotate, SLOT(click()));

        QMetaObject::connectSlotsByName(GUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *GUIClass)
    {
        GUIClass->setWindowTitle(QApplication::translate("GUIClass", "Simple image editor", 0, QApplication::UnicodeUTF8));
        mnuOpen->setText(QApplication::translate("GUIClass", "Open", 0, QApplication::UnicodeUTF8));
        mnuSave->setText(QApplication::translate("GUIClass", "Save", 0, QApplication::UnicodeUTF8));
        mnuSave->setShortcut(QApplication::translate("GUIClass", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        mnuSaveAs->setText(QApplication::translate("GUIClass", "Save As ...", 0, QApplication::UnicodeUTF8));
        mnuSaveAs->setShortcut(QApplication::translate("GUIClass", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
        action_4->setText(QApplication::translate("GUIClass", "-", 0, QApplication::UnicodeUTF8));
        mnuExit->setText(QApplication::translate("GUIClass", "Exit", 0, QApplication::UnicodeUTF8));
        action_7->setText(QApplication::translate("GUIClass", "\"\320\241\320\265\321\200\321\213\320\271 \320\274\320\270\321\200\"", 0, QApplication::UnicodeUTF8));
        action_8->setText(QApplication::translate("GUIClass", "\320\234\320\265\320\264\320\270\320\260\320\275\320\275\320\260\321\217 \321\204\320\270\320\273\321\214\321\202\321\200\320\260\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        mnuAbout->setText(QApplication::translate("GUIClass", "About", 0, QApplication::UnicodeUTF8));
        mnuGrayscale->setText(QApplication::translate("GUIClass", "Grayscale", 0, QApplication::UnicodeUTF8));
        mnuHygramLinear->setText(QApplication::translate("GUIClass", "Hystogram Linear", 0, QApplication::UnicodeUTF8));
        mnuHygramChennel->setText(QApplication::translate("GUIClass", "Per-Chennel hystogram", 0, QApplication::UnicodeUTF8));
        mnuGreyWorld->setText(QApplication::translate("GUIClass", "Grey World", 0, QApplication::UnicodeUTF8));
        mnuMedian->setText(QApplication::translate("GUIClass", "Median", 0, QApplication::UnicodeUTF8));
        mnuGaussian->setText(QApplication::translate("GUIClass", "Gaussain", 0, QApplication::UnicodeUTF8));
        mnuSobel->setText(QApplication::translate("GUIClass", "Sobel", 0, QApplication::UnicodeUTF8));
        mnuScale->setText(QApplication::translate("GUIClass", "Scaling", 0, QApplication::UnicodeUTF8));
        mnuRotate->setText(QApplication::translate("GUIClass", "Rotate", 0, QApplication::UnicodeUTF8));
        mnuManually->setText(QApplication::translate("GUIClass", "Custom", 0, QApplication::UnicodeUTF8));
        mnuGlass->setText(QApplication::translate("GUIClass", "Glass", 0, QApplication::UnicodeUTF8));
        gbImage->setTitle(QApplication::translate("GUIClass", "File", 0, QApplication::UnicodeUTF8));
        btnOpen->setText(QApplication::translate("GUIClass", "Open", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("GUIClass", "Save", 0, QApplication::UnicodeUTF8));
        btnSaveAs->setText(QApplication::translate("GUIClass", "Save As...", 0, QApplication::UnicodeUTF8));
        gbFilters->setTitle(QApplication::translate("GUIClass", "Filters", 0, QApplication::UnicodeUTF8));
        btnGreyWorld->setText(QApplication::translate("GUIClass", "Grey World", 0, QApplication::UnicodeUTF8));
        btnMedian->setText(QApplication::translate("GUIClass", "Median", 0, QApplication::UnicodeUTF8));
        btnGrayscale->setText(QApplication::translate("GUIClass", "Grayscale", 0, QApplication::UnicodeUTF8));
        btnHygramLinear->setText(QApplication::translate("GUIClass", "Autoconrast", 0, QApplication::UnicodeUTF8));
        btnHygramChennel->setText(QApplication::translate("GUIClass", "Autolevels", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        editMedian->setToolTip(QApplication::translate("GUIClass", "Matrix radious", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        editMedian->setStatusTip(QApplication::translate("GUIClass", "Set matrix size", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        editMedian->setWhatsThis(QApplication::translate("GUIClass", "Set matrix size", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        editMedian->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        editMedian->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        editMedian->setInputMask(QString());
        editMedian->setText(QApplication::translate("GUIClass", "6", 0, QApplication::UnicodeUTF8));
        labelWarning->setText(QString());
        btnGaussian->setText(QApplication::translate("GUIClass", "Gaussian", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        editGaussianSigma->setToolTip(QApplication::translate("GUIClass", "Sigma", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        editGaussianSigma->setInputMask(QString());
        editGaussianSigma->setText(QApplication::translate("GUIClass", "1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        editGaussian->setToolTip(QApplication::translate("GUIClass", "Matrix radious", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        editGaussian->setText(QApplication::translate("GUIClass", "6", 0, QApplication::UnicodeUTF8));
        btnSobel->setText(QApplication::translate("GUIClass", "Sobel", 0, QApplication::UnicodeUTF8));
        btnScale->setText(QApplication::translate("GUIClass", "Scale", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        editScale->setToolTip(QApplication::translate("GUIClass", "Scale Factor", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        editScale->setStatusTip(QApplication::translate("GUIClass", "Scale factor", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        px_label0->setText(QApplication::translate("GUIClass", "px", 0, QApplication::UnicodeUTF8));
        px_label1->setText(QApplication::translate("GUIClass", "px", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GUIClass", "tms", 0, QApplication::UnicodeUTF8));
        btnRotate->setText(QApplication::translate("GUIClass", "Rotate", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        editRotate->setToolTip(QApplication::translate("GUIClass", "Rotation angle", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        editRotate->setStatusTip(QApplication::translate("GUIClass", "Rotation angle", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        editRotate->setText(QApplication::translate("GUIClass", "90", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("GUIClass", "\302\260", 0, QApplication::UnicodeUTF8));
        btnManually->setText(QApplication::translate("GUIClass", "Custom", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        editManuallyX->setToolTip(QApplication::translate("GUIClass", "Matrix width", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        editManuallyX->setText(QApplication::translate("GUIClass", "3", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        editManuallyY->setToolTip(QApplication::translate("GUIClass", "Matrix height", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        editManuallyY->setText(QApplication::translate("GUIClass", "3", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("GUIClass", "x", 0, QApplication::UnicodeUTF8));
        btnGlass->setText(QApplication::translate("GUIClass", "Glass", 0, QApplication::UnicodeUTF8));
        pbMain->setFormat(QApplication::translate("GUIClass", "%p%", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("GUIClass", "Filters", 0, QApplication::UnicodeUTF8));
        menu_3->setTitle(QApplication::translate("GUIClass", "Help", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("GUIClass", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GUIClass: public Ui_GUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
