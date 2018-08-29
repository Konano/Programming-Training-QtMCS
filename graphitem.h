#ifndef GRAPHITEM_H
#define GRAPHITEM_H
#include <QPainter>
#include <QGraphicsItem>
#include <QObject>
#include <QDebug>

#define pipeLength 45
#define pipeWidth 5

class GraphItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    GraphItem(int _x, int _y, int _width, int _height, bool _NotChange = false, QObject *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void switchEnable();
    void setEnable(bool status);
    bool isEnable();
    void setV(double _v);
    double getV();

private:
    int x, y, width, height;
    bool Enable, NotChange;
    double v = 0;

signals:
    void pipeChanged();
    void hoverEnter(QString);
    void hoverLeave();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

};

#endif // GRAPHITEM_H
