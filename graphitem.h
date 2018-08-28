#ifndef GRAPHITEM_H
#define GRAPHITEM_H
#include <QPainter>
#include <QGraphicsItem>
#include <QObject>
#include <QDebug>

#define pipeLength 40
#define pipeWidth 5

class GraphItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    GraphItem(int _x, int _y, int _width, int _height, bool _NotChange = false, QObject *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool Enable, NotChange;
    int x, y, width, height;
    GraphItem *adjacent[4];

    void setAdjacent(GraphItem *adj0, GraphItem *adj1, GraphItem *adj2 = NULL, GraphItem *adj3 = NULL);
    void updateSquare();
    void switchPipe();
    void openPipe();
    void closePipe();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // GRAPHITEM_H
