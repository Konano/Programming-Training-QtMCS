#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "config.h"
#include "calculate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 窗口大小
    setFixedSize(450, 510);

    size = 8;
    for(int i=0; i<size; i++) input[i] = i<2;
    for(int i=0; i<size; i++) output[i] = i<3;

    sceneNew();
}

void MainWindow::sceneNew()
{
    scene = new QGraphicsScene(this);
    ui->graphicsView->resize(431-(8-size)*(pipeLength+pipeWidth), 431-(8-size)*(pipeLength+pipeWidth));
    ui->graphicsView->setScene(scene);
    setFixedSize(450-(8-size)*(pipeLength+pipeWidth), 510-(8-size)*(pipeLength+pipeWidth));
}

void MainWindow::sceneDraw()
{
    delete scene;
    sceneNew();

    for(int i=0; i<size-1; i++)
        for(int j=0; j<size; j++)
        {
            pipeRow[i][j] = new GraphItem(pipeWidth+i*(pipeLength+pipeWidth), 0+j*(pipeLength+pipeWidth), pipeLength, pipeWidth);
            scene->addItem(pipeRow[i][j]);
        }

    for(int i=0; i<size; i++)
        for(int j=0; j<size-1; j++)
        {
            pipeCol[i][j] = new GraphItem(0+i*(pipeLength+pipeWidth), pipeWidth+j*(pipeLength+pipeWidth), pipeWidth, pipeLength);
            scene->addItem(pipeCol[i][j]);
        }

    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
        {
            square[i][j] = new GraphItem(0+i*(pipeLength+pipeWidth), 0+j*(pipeLength+pipeWidth), pipeWidth, pipeWidth, true);
            scene->addItem(square[i][j]);
        }

    for(int i=0; i<size; i++) if (input[i])
    {
        pipeIn[i] = new GraphItem(0+i*(pipeLength+pipeWidth), -pipeLength/2, pipeWidth, pipeLength/2, true);
        scene->addItem(pipeIn[i]);
    }

    for(int i=0; i<size; i++) if (output[i])
    {
        pipeOut[i] = new GraphItem(0+i*(pipeLength+pipeWidth), pipeWidth+(size-1)*(pipeLength+pipeWidth), pipeWidth, pipeLength/2, true);
        scene->addItem(pipeOut[i]);
    }

    // 相邻元素

    for(int i=0; i<size-1; i++)
        for(int j=0; j<size; j++)
            pipeRow[i][j]->setAdjacent(square[i][j],
                                       square[i+1][j]);

    for(int i=0; i<size; i++)
        for(int j=0; j<size-1; j++)
            pipeCol[i][j]->setAdjacent(square[i][j],
                                       square[i][j+1]);

    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
            square[i][j]->setAdjacent(i<size-1 ? pipeRow[i][j] : NULL,
                                      j<size-1 ? pipeCol[i][j] : NULL,
                                      i ? pipeRow[i-1][j] : NULL,
                                      j ? pipeCol[i][j-1] : NULL);
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

void MainWindow::on_actionRandom_triggered()
{
    for(int i=0; i<size-1; i++)
        for(int j=0; j<size; j++)
            if (rand()%100 < 90)
                pipeRow[i][j]->openPipe();
            else
                pipeRow[i][j]->closePipe();

    for(int i=0; i<size; i++)
        for(int j=0; j<size-1; j++)
            if (rand()%100 < 90)
                pipeCol[i][j]->openPipe();
            else
                pipeCol[i][j]->closePipe();
}

void MainWindow::on_actionSimulation_triggered()
{
    int i1=0; while (!input[i1]) i1++;
    int i2=i1+1; while (!input[i2]) i2++;
    int o1=0; while (!output[o1]) o1++;
    int o2=o1+1; while (!output[o2]) o2++;
    int o3=o2+1; while (!output[o3]) o3++;
    vector<double> length;
    for(int i=0; i<size; i++)
        for(int j=0; j<size-1; j++)
            if (pipeCol[i][j]->Enable) length.push_back(1); else length.push_back(0);
    for(int i=0; i<size-1; i++)
        for(int j=0; j<size; j++)
            if (pipeRow[i][j]->Enable) length.push_back(1); else length.push_back(0);
    for(int i=0; i<2+3; i++) length.push_back(1);
    vector<double> result = caluconspeed(size, length, i1, i2, o1, o2, o3);
    qDebug() << result[0] << result[1] << result[2] << endl;
}
