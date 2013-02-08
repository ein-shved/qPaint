#ifndef GUI_H
#define GUI_H

#include <string>
#include <vector>
#include <fstream>

#include <QtGui/QMainWindow>
#include <QDesktopWidget>
#include <QTextCodec>
#include <QMessageBox>
#include <QFileDialog>
#include <QClipboard>
#include <QTimer>
#include <QThread>
#include <QDesktopServices>
#include <QMutex>

#include "ui_gui.h"
#include "ui_Manually.h"

#include "../Engine/Engine.h"
#include "ImageScene.h"
#include "Validators.h"

class GUI;
class QFilterThread : public QThread
{
	Q_OBJECT

	Engine& m_lEngine;
	GUI *m_pGUI;

protected:
	void run();

public:
	QFilterThread(Engine& engine, GUI* in_pGUI) : m_lEngine(engine), m_pGUI(in_pGUI) {};
	void start (  Priority priority = InheritPriority );
public slots:
	void terminate();
};

class ManuallyTable : public QDialog {
	Q_OBJECT

private:
	QMainWindow* m_pGUI;
	Ui_ManuallyTable ui;
	TableValidator m_validator;
	void clearLVector();
	QVector<QVector<float> > m_matrix;
	int m_iWidth, m_iHeight;

private slots:
	void accept();
	void reject();
public:
	void init(int width, int height);
	ManuallyTable (QMainWindow* in_pGUI) : m_pGUI(in_pGUI) {
		ui.setupUi(this);
	}
	~ManuallyTable () {
	}
	const QVector<QVector<float> >& getMatrix() const;
};

class  QProgressEvent : public QEvent
{
public:
	QString sOperation;
	uint percent;
	QProgressEvent() : QEvent((QEvent::Type)(QEvent::User + 1)) {};
};
class DoneEvent : public QEvent {
public:
	DoneEvent() : QEvent((QEvent::Type)(QEvent::User + 2)) {};
};
class AcceptManualEvent : public QEvent {
public:
	AcceptManualEvent() : QEvent((QEvent::Type)(QEvent::User + 3)) {};
};
class RejectManualEvent : public QEvent {
public:
	RejectManualEvent() : QEvent((QEvent::Type)(QEvent::User + 4)) {};
};


class GUI : public QMainWindow
{
	Q_OBJECT

public:
	GUI( Engine engine = Engine(), QWidget *parent = 0, Qt::WFlags flags = 0);
	~GUI();


private slots:
	void onExit();
	
	void onOpen();
	void onSave();
	void onSaveAs();
	void onAbout();

	void onGrayscale();
	void onHystogramLinear();
	void onHystogramPerChennel();
	void onGreyWorld();
	void onMedian();

	void onGaussian();
	void onEditGaussian_TextChanged(QString);
	void onEditGaussianSigma_TextChanged(QString);

	void onSobel();
	void onScale();
	void onRotate();
	void onManually();
	void onManuallyRun();
	void onGlass();

protected:
	void closeEvent(QCloseEvent *event);
	bool event(QEvent *event);
	void resizeEvent ( QResizeEvent *event );

private:
	Ui::GUIClass ui;
	Engine m_Engine;
	QString m_sPath;
	ImageScene *m_pCurrentScene;
	QFilterThread m_FilterThread;
	QMutex m_Mutex;

	void onInit();
	void updateImage();
	void enableControls(bool in_bEnable);
	void enableFilters(bool in_bEnable);
	void showProgressBar(bool in_bVisible);
	void calcGVGeometry ();

	ScaleValidator m_scaleValidator;
	MedianValidator m_medianValidator;
	GaussianValidator m_gaussianValidator;
	GaussianSigmaValidator m_gaussianSigmaValidator;
	ManualValidator m_manualValidator;

	struct CallbackData {
		GUI* pGUI;
		QString sOperation;
		CallbackData (GUI *in_pGUI = NULL, const QString &in_sOperation = ""):
			pGUI(in_pGUI), sOperation(in_sOperation) {}
	};
        Callback m_Callback;
        static void callback(uint percent, void* pThis);

	ManuallyTable m_pManTable;

	CallbackData 	m_DataEmpty,m_DataGrayscale, m_DataHygram, m_DataHygramChennel,m_DataGreyWorld,
			m_DataMedian, m_DataGaussian, m_DataSobel, m_DataScale, m_DataRotate, m_DataManual,
			m_DataGlass;

	friend class QFilterThread;
};


#endif // GUI_H
