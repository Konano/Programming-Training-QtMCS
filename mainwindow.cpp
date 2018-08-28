#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    for(int i=0; i<7; i++)
        for(int j=0; j<8; j++)
        {
            pipeRow[i][j] = new GraphItem(5+i*45, 0+j*45, 40, 5);
            scene->addItem(pipeRow[i][j]);
        }

    for(int i=0; i<8; i++)
        for(int j=0; j<7; j++)
        {
            pipeCol[i][j] = new GraphItem(0+i*45, 5+j*45, 5, 40);
            scene->addItem(pipeCol[i][j]);
        }

    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
            square[i][j] = new GraphItem(0+i*45, 0+j*45, 5, 5, true);
            scene->addItem(square[i][j]);
        }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCreate_triggered()
{
    qDebug("Test");
    Config config(this);
    config.exec();
}
