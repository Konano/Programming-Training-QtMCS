#include "config.h"
#include "ui_config.h"

Config::Config(int inFlow0, int inFlow1, int inConcen0, int inConcen1, int random, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config)
{
    ui->setupUi(this);

    flowLimit = new QIntValidator(0, inflowMaxLimit, this);
    hundredLimit = new QIntValidator(0, 100, this);

    ui->lineEdit_flow0->setText(QString::number(inFlow0));
    ui->lineEdit_flow1->setText(QString::number(inFlow1));
    ui->lineEdit_concen0->setText(QString::number(inConcen0));
    ui->lineEdit_concen1->setText(QString::number(inConcen1));
    ui->lineEdit_random->setText(QString::number(random));

    ui->lineEdit_flow0->setValidator(flowLimit);
    ui->lineEdit_flow1->setValidator(flowLimit);
    ui->lineEdit_concen0->setValidator(hundredLimit);
    ui->lineEdit_concen1->setValidator(hundredLimit);
    ui->lineEdit_random->setValidator(hundredLimit);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(finish()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

Config::~Config()
{
    delete ui;
}

void Config::finish()
{
    emit finished(ui->lineEdit_flow0->text().toInt(),
                  ui->lineEdit_flow1->text().toInt(),
                  ui->lineEdit_concen0->text().toInt(),
                  ui->lineEdit_concen1->text().toInt(),
                  ui->lineEdit_random->text().toInt());
    accept();
}
