#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "config.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    size = 8;
    for(int i=0; i<size; i++) input[i] = i<2;
    for(int i=0; i<size; i++) output[i] = i<3;

    sceneNew();
}

void MainWindow::sceneNew()
{
    scene = new QGraphicsScene(this);
    ui->graphicsView->resize(431-(8-size)*45, 431-(8-size)*45);
    this->resize(450-(8-size)*45, 517-(8-size)*45);
    ui->graphicsView->setScene(scene);
}

void MainWindow::sceneDraw()
{
    delete scene;
    sceneNew();

    for(int i=0; i<size-1; i++)
        for(int j=0; j<size; j++)
        {
            pipeRow[i][j] = new GraphItem(5+i*45, 0+j*45, 40, 5);
            scene->addItem(pipeRow[i][j]);
        }

    for(int i=0; i<size; i++)
        for(int j=0; j<size-1; j++)
        {
            pipeCol[i][j] = new GraphItem(0+i*45, 5+j*45, 5, 40);
            scene->addItem(pipeCol[i][j]);
        }

    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
        {
            square[i][j] = new GraphItem(0+i*45, 0+j*45, 5, 5, true);
            scene->addItem(square[i][j]);
        }

    for(int i=0; i<size; i++) if (input[i])
    {
        pipeIn[i] = new GraphItem(0+i*45, 5-45, 5, 40, true);
        scene->addItem(pipeIn[i]);
    }

    for(int i=0; i<size; i++) if (output[i])
    {
        pipeOut[i] = new GraphItem(0+i*45, 5+(size-1)*45, 5, 40, true);
        scene->addItem(pipeOut[i]);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCreate_triggered()
{
    Config config(this);
    connect(&config, SIGNAL(finish(int,bool*,bool*)), this, SLOT(create(int,bool*,bool*)));
    config.exec();
}

void MainWindow::create(int _size, bool *_input, bool *_output)
{
    size = _size;
    for(int i=0; i<size; i++) input[i]=_input[i];
    for(int i=0; i<size; i++) output[i]=_output[i];

    sceneDraw();
}
