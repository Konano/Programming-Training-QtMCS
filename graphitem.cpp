#include "graphitem.h"

GraphItem::GraphItem(int _x, int _y, int _width, int _height, bool _NotChange)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    Enable = true;
    NotChange = _NotChange;
}

QRectF GraphItem::boundingRect() const
{
    return QRectF(x,y,width,height);
}

void GraphItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);

    if (Enable)
    {
        brush.setColor(Qt::blue);
    }
    else
    {
        brush.setColor(Qt::red);
    }

    painter->fillRect(rec, brush);
    painter->drawRect(rec);
}

void GraphItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (NotChange == false) Enable ^= 1;
    update();
    QGraphicsItem::mousePressEvent(event);
}

