#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "createconfig.h"
#include <QtCore>
#include <QtGui>
#include "graphitem.h"

#define inflowMaxLimit 200
#define initRandom 90

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
    void updateText();
    void Simulation();

private slots:
    void on_actionCreate_triggered();

    void on_actionRandom_triggered();

    void on_actionConfig_triggered();

    void create(int, bool*, bool*);
    void updateConfig(int, int, int, int, int);
    void chipChanged();
    void on_actionSwitch_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    int size;
    bool input[8], output[8];
    GraphItem *pipeRow[7][8], *pipeCol[8][7], *cross[8][8], *pipeIn[8], *pipeOut[8];
    QGraphicsTextItem *textitem[3];
    bool Randoming = false;
    int inFlow0, inFlow1;
    int random;
    int inConcen0, inConcen1;
};

#endif // MAINWINDOW_H
