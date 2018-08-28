#ifndef GRAPHITEM_H
#define GRAPHITEM_H
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>

class GraphItem : public QGraphicsItem
{
public:
    GraphItem(int _x, int _y, int _width, int _height, bool _NotChange = false);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool Enable, NotChange;
    int x, y, width, height;

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

};

#endif // GRAPHITEM_H
