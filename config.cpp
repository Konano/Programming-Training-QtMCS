#include "config.h"
#include "ui_config.h"

Config::Config(int inflow0, int inflow1, int random, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config)
{
    ui->setupUi(this);

    inputLimit = new QIntValidator(0, inflowMaxLimit, this);
    randomLimit = new QIntValidator(0, 100, this);

    ui->lineEdit_input0->setText(QString::number(inflow0));
    ui->lineEdit_input1->setText(QString::number(inflow1));
    ui->lineEdit_random->setText(QString::number(random));

    ui->lineEdit_input0->setValidator(inputLimit);
    ui->lineEdit_input1->setValidator(inputLimit);
    ui->lineEdit_random->setValidator(randomLimit);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(finish()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

Config::~Config()
{
    delete ui;
}

void Config::finish()
{
    emit finished(ui->lineEdit_input0->text().toInt(),
                  ui->lineEdit_input1->text().toInt(),
                  ui->lineEdit_random->text().toInt());
    accept();
}
