#include "image.h"

Image::Image(QObject *parent) : QObject(parent)
{
    pix_img.load("image.png");
}

QRectF Image::boundingRect() const        //位图元限定区域范围
{
    qreal adjust =2;
    return QRectF(-pix_img.width()/2-adjust,-pix_img.height()/2-adjust,pix_img.width()+adjust*2,pix_img.height()+adjust*2);
}
