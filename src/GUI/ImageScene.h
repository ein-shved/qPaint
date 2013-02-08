#ifndef _IMAGE_SCENE_H
#define _IMAGE_SCENE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

class ImageScene : public QGraphicsScene {
	Q_OBJECT
private:
	QGraphicsRectItem* m_pSelection;
	QGraphicsPixmapItem* m_pPixmap;
	QPen m_SelectionPen;
	QBrush m_SelectionBrush;
	QPointF m_SelectionPosition;
public:
	ImageScene () : QGraphicsScene(), m_pSelection (NULL), m_pPixmap (NULL),
			m_SelectionPen (Qt::DashDotLine), m_SelectionBrush(Qt::Dense6Pattern)
	{
		m_SelectionPen.setColor ( QColor(255,0,0)); //red
		m_SelectionBrush.setColor ( QColor(0,0,255)); //blue
	}
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent*);
	void mouseMoveEvent(QGraphicsSceneMouseEvent*);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
public:
	QRect getSelection () const;
	void setSelection (const ImageScene& other);
	void resetSelection ();
	QGraphicsPixmapItem* addPixmap(QPixmap in_Pixmap);
};

#endif //_IMAGE_SCENE_H