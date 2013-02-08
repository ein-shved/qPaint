#include "ImageScene.h"

void ImageScene::mousePressEvent(QGraphicsSceneMouseEvent* in_mEvent) {
	if (m_pPixmap == NULL) {
		return;
	}
	if ( 	in_mEvent->scenePos().x() < m_pPixmap->offset().x() ||
		in_mEvent->scenePos().y() < m_pPixmap->offset().y() ||
		in_mEvent->scenePos().x() - m_pPixmap->offset().x() > m_pPixmap->pixmap().rect().width() ||
		in_mEvent->scenePos().y() - m_pPixmap->offset().y() > m_pPixmap->pixmap().rect().height())
	{
		if ( m_pSelection != NULL ) {
			QGraphicsScene::removeItem ( m_pSelection);
			m_pSelection = NULL;
		}
		return;
	}
	if (m_pSelection != NULL) {
		QGraphicsScene::removeItem ( m_pSelection);
	}
	m_pSelection = QGraphicsScene::addRect (in_mEvent->scenePos().x(),
						in_mEvent->scenePos().y(),
						0,0, m_SelectionPen, m_SelectionBrush);
	m_pSelection->setParentItem (m_pPixmap);
	m_SelectionPosition = m_pSelection->rect().topLeft();

	if  ( 	m_pSelection->rect().width() < 1 ||
		m_pSelection->rect().height() < 1 )
	{
		m_pSelection->setVisible(false);
	} else {
		m_pSelection->setVisible(true);
	}
}
void ImageScene::mouseMoveEvent(QGraphicsSceneMouseEvent* in_mEvent) {
	if (m_pPixmap == NULL) {
		return;
	}
	qreal x = in_mEvent->scenePos().x(), y = in_mEvent->scenePos().y();
	if ( 	x < m_pPixmap->offset().x() ) {
		x = m_pPixmap->offset().x();
	} else if ( x - m_pPixmap->offset().x() >= m_pPixmap->pixmap().rect().width() ) {
		x = m_pPixmap->pixmap().rect().width() + m_pPixmap->offset().x() - 1;
	}
	if ( y < m_pPixmap->offset().y() ) {
		y = m_pPixmap->offset().y();
	} else if ( y - m_pPixmap->offset().y() >= m_pPixmap->pixmap().rect().height() ) {
		y = m_pPixmap->pixmap().rect().height() + m_pPixmap->offset().y() - 1;
	}
	if (m_pSelection != NULL) {
		QRectF rect;
		rect.setCoords ( m_SelectionPosition.x(),
				 m_SelectionPosition.y(),
				 x,y );
		m_pSelection->setRect ( rect.normalized());
	} else {
		m_pSelection = QGraphicsScene::addRect (x,y,0,0, m_SelectionPen, m_SelectionBrush);
		m_pSelection->setParentItem (m_pPixmap);
		m_SelectionPosition = m_pSelection->rect().topLeft();
	}

	if  ( 	m_pSelection->rect().width() < 1 ||
		m_pSelection->rect().height() < 1 )
	{
		m_pSelection->setVisible(false);
	} else {
		m_pSelection->setVisible(true);
	}
}
void ImageScene::mouseReleaseEvent(QGraphicsSceneMouseEvent*) {
	if (m_pSelection != NULL) {
		if  ( 	m_pSelection->rect().width() < 1 ||
			m_pSelection->rect().height() < 1 )
		{
			QGraphicsScene::removeItem ( m_pSelection);
			m_pSelection = NULL;
		}
	}
}
QRect ImageScene::getSelection () const
{
	if ( m_pSelection == NULL) {
		return QRect();
	}
	QRectF r=m_pSelection->rect();
	return QRect ( r.x()- m_pPixmap->offset().x(), r.y() - m_pPixmap->offset().y(), r.width(), r.height() );
}
void ImageScene::setSelection (const ImageScene& other)
{
	if (m_pSelection != NULL) {
		QGraphicsScene::removeItem ( m_pSelection);
	}
	m_pSelection = other.m_pSelection;
	if (m_pSelection != NULL) {
		QGraphicsScene::addItem (m_pSelection);
	}
}
void ImageScene::resetSelection ()
{
	if (m_pSelection != NULL) {
		QGraphicsScene::removeItem ( m_pSelection);
		m_pSelection = NULL;
	}
}
QGraphicsPixmapItem* ImageScene::addPixmap(QPixmap in_Pixmap) {
	if (m_pPixmap != NULL ) {
		QGraphicsScene::removeItem ( m_pPixmap);
	}
	m_pPixmap = QGraphicsScene::addPixmap(in_Pixmap);
	resetSelection();
	return m_pPixmap;
}
