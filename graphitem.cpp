#include "graphitem.h"
#include <QDebug>

GraphItem::GraphItem(int _x, int _y, int _width, int _height, bool _NotChange, QObject *parent) :
    Enable(true), NotChange(_NotChange), x(_x), y(_y), width(_width), height(_height), QObject(parent)
{
}

void GraphItem::setAdjacent(GraphItem *adj0, GraphItem *adj1, GraphItem *adj2, GraphItem *adj3)
{
    adjacent[0] = adj0;
    adjacent[1] = adj1;
    adjacent[2] = adj2;
    adjacent[3] = adj3;
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
        brush.setColor(QColor(225,225,225));
    }

    painter->fillRect(rec, brush);
}

void GraphItem::updateSquare()
{
    for(int i=0; i<4; i++) if (adjacent[i] != NULL)
    {
        if (adjacent[i]->Enable)
        {
            Enable = true;
            update();
            return;
        }
    }
    Enable = false;
    update();
}

void GraphItem::switchPipe()
{
    Enable ^= 1;
    adjacent[0]->updateSquare();
    adjacent[1]->updateSquare();
    update();
}

void GraphItem::openPipe()
{
    if (Enable == false) switchPipe();
}

void GraphItem::closePipe()
{
    if (Enable == true) switchPipe();
}

void GraphItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (NotChange == false) switchPipe();
    QGraphicsItem::mousePressEvent(event);
}
