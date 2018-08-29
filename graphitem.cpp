#include "graphitem.h"
#include <QDebug>
#include <QColor>
#include <cmath>

GraphItem::GraphItem(int _x, int _y, int _width, int _height, bool _NotChange, QObject *parent) :
    x(_x), y(_y), width(_width), height(_height), Enable(true), NotChange(_NotChange), QObject(parent)
{
    if (_NotChange == false) setAcceptHoverEvents(true);
}

QRectF GraphItem::boundingRect() const
{
    return QRectF(x,y,width,height);
}

QColor flowColor(double v)
{
    if (v > 300)
        return QColor(std::min(std::max((int)round((400-v)/100*256-0.5),0),255),
                      0,
                      0);
    else
        return QColor(std::min(std::max((int)round((v-150)/150*256-0.5),0),255),
                      std::min(std::max((int)round((150-fabs(v-150))/150*256-0.5),0),255),
                      std::min(std::max((int)round((150-v)/150*256-0.5),0),255));
}

void GraphItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);

    if (Enable)
    {
        brush.setColor(flowColor(v));
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

void GraphItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (Enable) emit hoverEnter(QString("Flow rate in the pipe: ")+QString::number(v));
}

void GraphItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (Enable) emit hoverLeave();
}

void GraphItem::setV(double _v)
{
    v = _v;
    update();
}

double GraphItem::getV()
{
    return v;
}
