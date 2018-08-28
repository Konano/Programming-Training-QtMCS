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

private:
    int x, y, width, height;
    bool Enable, NotChange;

signals:
    void pipeChanged();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // GRAPHITEM_H
