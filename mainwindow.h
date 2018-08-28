#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "config.h"
#include <QtCore>
#include <QtGui>
#include "graphitem.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void sceneNew();
    void sceneDraw();
    void updateCross();
    void Simulation();

private slots:
    void on_actionCreate_triggered();

    void on_actionRandom_triggered();

    void create(int, bool*, bool*);
    void chipChanged();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    int size; bool input[8], output[8];
    GraphItem *pipeRow[7][8], *pipeCol[8][7], *cross[8][8], *pipeIn[8], *pipeOut[8];
    QGraphicsTextItem *textitem[3];

    bool Randoming = false;
};

#endif // MAINWINDOW_H
