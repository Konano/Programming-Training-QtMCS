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

MainWindow::~MainWindow()
{
    delete ui;
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
            connect(pipeRow[i][j], SIGNAL(pipeChanged()), this, SLOT(chipChanged()));
            scene->addItem(pipeRow[i][j]);
        }

    for(int i=0; i<size; i++)
        for(int j=0; j<size-1; j++)
        {
            pipeCol[i][j] = new GraphItem(0+i*(pipeLength+pipeWidth), pipeWidth+j*(pipeLength+pipeWidth), pipeWidth, pipeLength);
            connect(pipeCol[i][j], SIGNAL(pipeChanged()), this, SLOT(chipChanged()));
            scene->addItem(pipeCol[i][j]);
        }

    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
        {
            cross[i][j] = new GraphItem(0+i*(pipeLength+pipeWidth), 0+j*(pipeLength+pipeWidth), pipeWidth, pipeWidth, true);
            scene->addItem(cross[i][j]);
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

    int tmp = 0;
    for(int i=0; i<3; i++)
    {
        while (!output[tmp]) tmp++;
        textitem[i] = new QGraphicsTextItem();
        textitem[i]->setPos(QPointF(tmp*(pipeLength+pipeWidth)-pipeLength/2,
                                    pipeWidth+(size-1)*(pipeLength+pipeWidth)+pipeLength/2));
        scene->addItem(textitem[i]);
        tmp++;
    }
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
    Simulation();
}

void MainWindow::on_actionRandom_triggered()
{
    for(int i=0; i<size-1; i++)
        for(int j=0; j<size; j++)
            pipeRow[i][j]->setEnable(rand()%100 < 90);

    for(int i=0; i<size; i++)
        for(int j=0; j<size-1; j++)
            pipeCol[i][j]->setEnable(rand()%100 < 90);
}

void MainWindow::chipChanged()
{
    updateCross();
    Simulation();
}

void MainWindow::updateCross()
{
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
        {
            if (i<size-1 && pipeRow[i][j]->isEnable()) { cross[i][j]->setEnable(true); continue; }
            if (j<size-1 && pipeCol[i][j]->isEnable()) { cross[i][j]->setEnable(true); continue; }
            if (i && pipeRow[i-1][j]->isEnable()) { cross[i][j]->setEnable(true); continue; }
            if (j && pipeCol[i][j-1]->isEnable()) { cross[i][j]->setEnable(true); continue; }
            cross[i][j]->setEnable(false);
        }
}

void MainWindow::Simulation()
{
    int i1=0; while (!input[i1]) i1++;
    int i2=i1+1; while (!input[i2]) i2++;
    int o1=0; while (!output[o1]) o1++;
    int o2=o1+1; while (!output[o2]) o2++;
    int o3=o2+1; while (!output[o3]) o3++;
    vector<double> length;
    for(int i=0; i<size; i++)
        for(int j=0; j<size-1; j++)
            if (pipeCol[i][j]->isEnable()) length.push_back(1); else length.push_back(0);
    for(int i=0; i<size-1; i++)
        for(int j=0; j<size; j++)
            if (pipeRow[i][j]->isEnable()) length.push_back(1); else length.push_back(0);
    for(int i=0; i<2+3; i++) length.push_back(1);
    vector<double> result = caluconspeed(size, length, i1, i2, o1, o2, o3);

    for(int i=0; i<3; i++)
        textitem[i]->setPlainText(QString::number(result[i]));
    update();
}
