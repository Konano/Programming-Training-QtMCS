#include "graphitem.h"
#include <QDebug>

GraphItem::GraphItem(int _x, int _y, int _width, int _height, bool _NotChange, QObject *parent) :
    x(_x), y(_y), width(_width), height(_height), Enable(true), NotChange(_NotChange), QObject(parent)
{
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
        brush.setColor(Qt::white);
    }

    painter->fillRect(rec, brush);
}

void GraphItem::switchEnable()
{
    Enable ^= 1;
    emit pipeChanged();
    update();
}

void GraphItem::setEnable(bool status)
{
    if (Enable != status) switchEnable();
}

bool GraphItem::isEnable()
{
    return Enable;
}

void GraphItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (NotChange == false) switchEnable();
    QGraphicsItem::mousePressEvent(event);
}
