#include "gui.h"
#include <iostream>
#include <stdexcept>
#include <QCloseEvent>

#include "../Engine/Filters/Hystogram.h"
#include "../Engine/Filters/GreyWorld.h"
#include "../Engine/Filters/Convolution.h"
#include "../Engine/Filters/Sobel.h"
#include "../Engine/Filters/Interpolation.h"
#include "../Engine/Filters/Manually.h"
#include "../Engine/Filters/Supplementary.h"
#include "../Engine/Filters/GaussianS.h"

using namespace std;
void GUI::onInit()
{
	QRect qrGeometry;
	QSize szWindow;

	//move window to screen center
	qrGeometry = frameGeometry();
	qrGeometry.moveCenter(QDesktopWidget().availableGeometry().center());
	move(qrGeometry.topLeft());

	showProgressBar (false);

	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

	m_pCurrentScene = NULL;
	updateImage();
	setAttribute(Qt::WA_AlwaysShowToolTips, true);

	ui.editScale->setValidator(&m_scaleValidator);
	ui.editMedian->setValidator(&m_medianValidator);
	ui.editGaussian->setValidator(&m_gaussianValidator);
	ui.editGaussianSigma->setValidator(&m_gaussianSigmaValidator);
	ui.editManuallyX->setValidator(&m_manualValidator);
	ui.editManuallyY->setValidator(&m_manualValidator);
}

void GUI::updateImage()
{
	if (m_Engine.getImage().isNull()) {
		enableFilters(false);
		return;
	}
	QPixmap pmNew = QPixmap::fromImage(m_Engine.getImage());
	ImageScene *pNewScene = new ImageScene;
	pNewScene->addPixmap(pmNew);
	ui.gvMain->setScene(pNewScene);
	if (m_pCurrentScene != NULL) {
		pNewScene->setSelection ( *m_pCurrentScene);
		delete m_pCurrentScene;
	}
	m_pCurrentScene = pNewScene;
	enableFilters(true);
}
void GUI::closeEvent(QCloseEvent *event)
{
	if (m_FilterThread.isRunning()) {
		QMessageBox mBox (QMessageBox::Information, "Working", "\n\tWait a bit\t\t", QMessageBox::Ok);
		mBox.exec();
		event->ignore();
	}
	
}
void GUI::onExit()
{
	this->close();
}

void GUI::onOpen()
{
	QString sPath = QFileDialog::getOpenFileName(this, "Open an image",
		m_sPath, "Images(*.jpg *.jpeg *.bmp *.png);;JPEG(*.jpg *.jpeg);;BMP(*.bmp);;PNG(*.png);;All files (*.*)");
	if (sPath.isEmpty()) return;

	if (!m_Engine.load(sPath))
	{
		QMessageBox::critical(this, "Error", "Can not to open the image.");
		return;
	};

	if ( m_pCurrentScene != NULL )
		m_pCurrentScene->resetSelection();
	updateImage();
	m_sPath = sPath;
}

void GUI::onSaveAs()
{
	QString sPath = QFileDialog::getSaveFileName(this, "Save an image",
		m_sPath,"Images(*.jpg *.jpeg *.bmp *.png);;JPEG(*.jpg *.jpeg);;BMP(*.bmp);;PNG(*.png);;All files (*.*)");
	if (sPath.isEmpty()) return;

	if (!m_Engine.save(sPath))
	{
		QMessageBox::critical(this, "Error","Can not to save an image.");
		return;
	};

	m_sPath = sPath;
}

void GUI::onSave()
{
	if (!m_Engine.save(m_sPath))
	{
		QMessageBox::critical(this, "Error","Can not to save an image.");
		return;
	}
}
void GUI::onAbout ()
{
	QMessageBox::about (this, "About",
		"\tSimple image editor\t\nBy\n\tShvedov Jury, 321 group\t\nPowered by\t\n\tMediaLab\t\n\tCMC MSU 2012y\t");
}
void QFilterThread::start (  Priority priority )
{
	if ( m_lEngine.getImage().isNull() )
		return;
	setTerminationEnabled(true);
	QThread::start ( priority);
}
void QFilterThread::run()
{
	setTerminationEnabled(true);
	try {
		m_lEngine.launch();
	} catch ( const logic_error &err) {
		QMessageBox::critical(m_pGUI, "Ошибка обработки изображения.", err.what() );
	} catch ( ... ) {
		QMessageBox::critical(m_pGUI, "Ошибка обработки изображения.", "Неизвестная ошибка" );
	}
	QCoreApplication::postEvent( m_pGUI, new DoneEvent);
}
void QFilterThread::terminate()
{
	m_pGUI->m_Mutex.tryLock();
	QThread::terminate();
}
void GUI::onGrayscale(){
	m_Callback.setExtra (&m_DataGrayscale);
        m_Engine.filter( Grayscale (m_pCurrentScene->getSelection(), m_Callback) );
	enableControls(false);
	m_FilterThread.start();
}
void GUI::onHystogramLinear(){
	m_Callback.setExtra (&m_DataHygram);
        m_Engine.filter( HystogramLinear (m_pCurrentScene->getSelection(), m_Callback) );
	enableControls(false);
	m_FilterThread.start();
}
void GUI::onHystogramPerChennel(){
	m_Callback.setExtra (&m_DataHygramChennel);
        m_Engine.filter( HystogramPerChennel (m_pCurrentScene->getSelection(), m_Callback) );
	enableControls(false);
	m_FilterThread.start();
}
void GUI::onGreyWorld(){
	m_Callback.setExtra (&m_DataGreyWorld);
        m_Engine.filter( GreyWorld (m_pCurrentScene->getSelection(), m_Callback) );
	enableControls(false);
	m_FilterThread.start();
}
void GUI::onMedian(){
	if ( ui.editMedian->text().isEmpty() ) {
		ui.editMedian->setFocus(Qt::OtherFocusReason);
		return;
	}
	int value = ui.editMedian->text().toInt();
	if ( value == 0 ){
		ui.editGaussian->setFocus(Qt::OtherFocusReason);
		return;
	}
	value = 2*value - 1;
	m_Callback.setExtra (&m_DataMedian);
        m_Engine.filter( Median (m_pCurrentScene->getSelection(), m_Callback,value) );
	enableControls(false);
	m_FilterThread.start();
}
void GUI::onGaussian(){
	if ( ui.editGaussian->text().isEmpty() ) {
		ui.editGaussian->setFocus(Qt::OtherFocusReason);
		return;
	}
	if ( ui.editGaussianSigma->text().isEmpty() ) {
		ui.editGaussian->setFocus(Qt::OtherFocusReason);
		return;
	}
	int value = ui.editGaussian->text().toInt();
	if ( value == 0 ){
		ui.editGaussian->setFocus(Qt::OtherFocusReason);
		return;
	}
	value = 2*value - 1;
	float sigma = ui.editGaussianSigma->text().toFloat();
	m_Callback.setExtra (&m_DataGaussian);
        m_Engine.filter( Gaussian (m_pCurrentScene->getSelection(), m_Callback,value,sigma) );
	enableControls(false);
	m_FilterThread.start();
}
void GUI::onEditGaussian_TextChanged(QString){
	int size = ui.editGaussian->text().toInt();
	float sigma = ((float)size)/6;
	QString sSigma;
	sSigma.setNum (sigma);
	ui.editGaussianSigma->setText(sSigma.remove(4,sSigma.size()));
}
void GUI::onEditGaussianSigma_TextChanged(QString){
	float value = ui.editGaussianSigma->text().toFloat();
	int size = 6*value;
	if ( size == 0 )
		size = 1;
	QString sSigma;
	sSigma.setNum (size);
	ui.editGaussian->setText(sSigma);
}
void GUI::onSobel() {
	m_Callback.setExtra (&m_DataSobel);
        m_Engine.filter( Sobel (m_pCurrentScene->getSelection(), m_Callback) );
	enableControls(false);
	m_FilterThread.start();
}
void GUI::onScale() {
	if ( ui.editScale->text().isEmpty() ) {
		ui.editScale->setFocus(Qt::OtherFocusReason);
		return;
	}
	float fFactor = ui.editScale->text().toFloat();
	if ( fFactor < 0.01 || fFactor > 10 ) {
		ui.editScale->setFocus(Qt::OtherFocusReason);
		return;
	}
	m_Callback.setExtra (&m_DataScale);
        m_Engine.filter( Scaling (m_pCurrentScene->getSelection(), m_Callback, fFactor) );
	enableControls(false);
	m_FilterThread.start();
}
#ifndef PI
#define PI 3.14159265359
#endif //PI

void GUI::onRotate() {
	if ( ui.editRotate->text().isEmpty() ) {
		ui.editRotate->setFocus(Qt::OtherFocusReason);
		return;
	}
	float fAngle = ((float)ui.editRotate->text().toInt()) * PI / 180;
	m_Callback.setExtra (&m_DataRotate);
        m_Engine.filter( Rotation (m_pCurrentScene->getSelection(), m_Callback, fAngle) );
	enableControls(false);
	m_FilterThread.start();
}

void GUI::onManually()  {
	size_t x = ui.editManuallyX->text().toUInt();
	size_t y = ui.editManuallyY->text().toUInt();
	if ( x < 3 ) {
		ui.editManuallyX->setFocus(Qt::OtherFocusReason);
		return;
	}
	if ( y < 3 ) {
		ui.editManuallyY->setFocus(Qt::OtherFocusReason);
		return;
	}

	enableControls(false);

	m_pManTable.init(x,y);
	m_pManTable.show();
}
void GUI::onManuallyRun () {
	m_Callback.setExtra (&m_DataManual);
        m_Engine.filter( Manually (m_pCurrentScene->getSelection(), m_Callback, m_pManTable.getMatrix()) );
	enableControls(false);
	m_FilterThread.start();
}
void GUI::onGlass() {
	m_Callback.setExtra (&m_DataGlass);
        m_Engine.filter( Glass (m_pCurrentScene->getSelection(), m_Callback) );
	enableControls(false);
	m_FilterThread.start();
}

GUI::GUI(Engine engine, QWidget *parent, Qt::WFlags flags) : QMainWindow(parent, flags),
	m_Engine(engine), m_sPath(engine.path()), m_pCurrentScene(NULL), m_FilterThread(m_Engine, this),
	m_Callback (callback, this),  m_pManTable(this),
	m_DataEmpty(this,""),m_DataGrayscale (this, "Grayscale"), m_DataHygram(this, "Linear hystogram"),
	m_DataHygramChennel ( this, "Per-Chennel hystogram" ), m_DataGreyWorld ( this, "Grey World" ),
	m_DataMedian ( this, "Median" ), m_DataGaussian ( this, "Gaussian" ), m_DataSobel ( this, "Sobel" ),
	m_DataScale ( this, "Scaling" ), m_DataRotate ( this, "Rotation" ), m_DataManual ( this, "Custom" ),
	m_DataGlass ( this, "Glass" )
{
	ui.setupUi(this);
	onInit();

	connect(ui.mnuExit, SIGNAL(activated()), this, SLOT(onExit()));

	connect(ui.btnOpen, SIGNAL(clicked()), this, SLOT(onOpen()));
	connect(ui.mnuOpen, SIGNAL(activated()), this, SLOT(onOpen()));

	connect(ui.btnSave, SIGNAL(clicked()), this, SLOT(onSave()));
	connect(ui.mnuSave, SIGNAL(activated()), this, SLOT(onSave()));

	connect(ui.btnSaveAs, SIGNAL(clicked()), this, SLOT(onSaveAs()));
	connect(ui.mnuSaveAs, SIGNAL(activated()), this, SLOT(onSaveAs()));

	connect(ui.btnGrayscale, SIGNAL(clicked()), this, SLOT(onGrayscale()));
	connect(ui.mnuGrayscale, SIGNAL(activated()), this, SLOT(onGrayscale()));

	connect(ui.btnHygramLinear, SIGNAL(clicked()), this, SLOT(onHystogramLinear()));
	connect(ui.mnuHygramLinear, SIGNAL(activated()), this, SLOT(onHystogramLinear()));

	connect(ui.btnHygramChennel, SIGNAL(clicked()), this, SLOT(onHystogramPerChennel()));
	connect(ui.mnuHygramChennel, SIGNAL(activated()), this, SLOT(onHystogramPerChennel()));

	connect(ui.btnGreyWorld, SIGNAL(clicked()), this, SLOT(onGreyWorld()));
	connect(ui.mnuGreyWorld, SIGNAL(activated()), this, SLOT(onGreyWorld()));

	connect(ui.btnMedian, SIGNAL(clicked()), this, SLOT(onMedian()));
	connect(ui.mnuMedian, SIGNAL(activated()), this, SLOT(onMedian()));

	connect(ui.btnSobel, SIGNAL(clicked()), this, SLOT(onSobel()));
	connect(ui.mnuSobel, SIGNAL(activated()), this, SLOT(onSobel()));

	connect(ui.btnScale, SIGNAL(clicked()), this, SLOT(onScale()));
	connect(ui.mnuScale, SIGNAL(activated()), this, SLOT(onScale()));

	connect(ui.btnRotate, SIGNAL(clicked()), this, SLOT(onRotate()));
	connect(ui.mnuRotate, SIGNAL(activated()), this, SLOT(onRotate()));

	connect(ui.btnManually, SIGNAL(clicked()), this, SLOT(onManually()));
	connect(ui.mnuManually, SIGNAL(activated()), this, SLOT(onManually()));

	connect(ui.btnGlass, SIGNAL(clicked()), this, SLOT(onGlass()));
	connect(ui.mnuGlass, SIGNAL(activated()), this, SLOT(onGlass()));

	connect(ui.mnuAbout, SIGNAL(activated()), this, SLOT(onAbout()));
}

GUI::~GUI()
{}
void GUI::callback(uint percent, void* pThis)
{
	CallbackData* data = (CallbackData*) pThis;
	QProgressEvent *pEvent = new QProgressEvent;
	pEvent->percent = percent;
	pEvent->sOperation = data->sOperation;
	QCoreApplication::postEvent( data->pGUI, pEvent);
}

void GUI::enableControls(bool in_bEnable)
{
	ui.gbImage->setEnabled(in_bEnable);
	ui.gbFilters->setEnabled(in_bEnable);
	ui.menuBar->setEnabled(in_bEnable);
}
void GUI::enableFilters(bool in_bEnable)
{
	ui.gbFilters->setEnabled(in_bEnable);
	ui.menu_2->setEnabled(in_bEnable);
}
void GUI::showProgressBar(bool in_bVisible)
{
	ui.pbMain->setVisible(in_bVisible);
	calcGVGeometry ();
}
void GUI::calcGVGeometry () {
	if ( ui.pbMain->isVisible()) {
	    const QRect& geom = ui.gvMain->geometry();
	    ui.gvMain->setGeometry ( geom.x(),
				     geom.y(),
				     geometry().width() - 10 - geom.x(),
				     geometry().height() - ui.pbMain->geometry().height() - 35 - geom.y() );

	} else {
	    const QRect& geom = ui.gvMain->geometry();
	    ui.gvMain->setGeometry ( geom.x(),
				     geom.y(),
				     geometry().width() - 10 - geom.x(),
				     geometry().height() - 30 - geom.y() );
	}
	ui.pbMain->setGeometry ( 10,
				 geometry().height() - 40,
				 geometry().width() - 20,
				 16 );
	ui.gbFilters->setGeometry ( 10, 120, 180,
				    geometry().height() - 512 + 341 );
}

bool GUI::event(QEvent *event)
{
	if (event->type() == (QEvent::Type)(QEvent::User + 1))
	{
		// Progress event
		QProgressEvent *pEvent = (QProgressEvent*)event;
		ui.pbMain->setFormat ( pEvent->sOperation + ": %p%" );
		ui.pbMain->setValue(pEvent->percent);
		if (pEvent->percent != 100){
			enableControls(false);
			showProgressBar (true);
		}
	}
	if (event->type() == (QEvent::Type)(QEvent::User + 2))
	{
		//DoneEvent
		enableControls(true);
		showProgressBar (false);
		updateImage();
	}
	if (event->type() == (QEvent::Type)(QEvent::User + 3))
	{
		//AcceptManualEvent
		onManuallyRun();
	}
	if (event->type() == (QEvent::Type)(QEvent::User + 4))
	{
		//RejectManualEvent
		enableControls(true);
		showProgressBar (false);
	}

	return QMainWindow::event(event);
}

void GUI::resizeEvent ( QResizeEvent* ev)
{
	calcGVGeometry();
	QMainWindow::resizeEvent(ev);
}

#define ROW_HEIGHT 20
#define COLUMN_WIDTH 50

void ManuallyTable::init (int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	if ( width > 15 ) {
		width = 15;
	}
	if ( height > 15 ) {
		height = 15;
	}
        ui.table->setObjectName(QString::fromUtf8("table"));
	ui.table->setGeometry(QRect(10, 30, 0, 0));
	//ui.table->setShowGrid(false);
        ui.table->horizontalHeader()->setVisible(false);
        ui.table->verticalHeader()->setVisible(false);

	int oldColumn = ui.table->columnCount ();
	int oldRow = ui.table->rowCount ();
	ui.table->setColumnCount(m_iWidth);
	ui.table->setRowCount(m_iHeight);

	QRect tableGeometry = ui.table->geometry();
	tableGeometry.setWidth ( width*COLUMN_WIDTH + 6 );
	tableGeometry.setHeight ( height*ROW_HEIGHT + 6 );
	ui.table->setGeometry ( tableGeometry );

	QSize windowSize ( width*COLUMN_WIDTH + 25,
			  height*ROW_HEIGHT + 75 );
	setMaximumSize (windowSize);
	setMinimumSize (windowSize);

	QRect buttonBoxGeometry ( windowSize.width() - 345,
				  windowSize.height() - 32,
				  341,32 );
	ui.buttonBox->setGeometry ( buttonBoxGeometry );

	for ( int i=0; i < m_iHeight; ++i )
		ui.table->setRowHeight(i,ROW_HEIGHT);
	for ( int i=0; i < m_iWidth; ++i ) {
		ui.table->setColumnWidth(i,COLUMN_WIDTH);
		for ( int j=0; j < m_iHeight; ++j ) {
			if ( oldColumn <= i || oldRow <= j) {
				QLineEdit *l = new QLineEdit();
				l->setValidator(&m_validator);
				l->setMaxLength(5);
				ui.table->setCellWidget ( i,j, l );
			}
		}
	}
}
void ManuallyTable::accept()
{
	m_matrix.resize (m_iWidth);
	for ( int i=0; i < m_iWidth; ++i ) {
		m_matrix[i].resize (m_iHeight);
		for ( int j=0; j < m_iHeight; ++j ) {
			QModelIndex modInd ( ui.table->indexAt(QPoint(COLUMN_WIDTH*i+1,ROW_HEIGHT*j+1)) );
			QLineEdit *l = dynamic_cast<QLineEdit*>(ui.table->indexWidget (modInd));
			if ( l->text().isEmpty() ) {
				l->setFocus(Qt::OtherFocusReason);
				m_matrix.clear();
				return;
			}
			m_matrix[i].append(l->text().toFloat());
		}

	}
	QCoreApplication::postEvent( m_pGUI, new AcceptManualEvent());
	QDialog::accept();
}
void ManuallyTable::reject()
{
	QCoreApplication::postEvent( m_pGUI, new RejectManualEvent());
	QDialog::reject();
}
const QVector<QVector<float> >& ManuallyTable::getMatrix() const
{
	return m_matrix;
}