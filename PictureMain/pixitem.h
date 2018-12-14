#ifndef PIXITEM_H
#define PIXITEM_H
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class PixItem : public QGraphicsItem
{
public:
    PixItem(QPixmap *pixmap);
    PixItem(const QPixmap &pixmap);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap pix;
};

#endif // PIXITEM_H
