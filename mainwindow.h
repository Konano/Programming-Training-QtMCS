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

private slots:
    void on_actionCreate_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    int size, input[2], output[3];
    GraphItem *pipeRow[7][8], *pipeCol[8][7], *square[8][8];
};

#endif // MAINWINDOW_H
