#ifndef IMAGE_H
#define IMAGE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>

class Image : public QObject
{
    Q_OBJECT
public:
    explicit Image(QObject *parent = 0);
     QRectF boundingRect() const;          //为图元限定区域范围，所有继承自QGraphicsItem的自定义图元都需实现此函数。
     //初始化载入图片
     void loadImage(const QString &fileName);
private:
     QPixmap pix_img;
signals:

public slots:
};

#endif // IMAGE_H
