#include "config.h"
#include "ui_config.h"

Config::Config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config)
{
    ui->setupUi(this);
}

Config::~Config()
{
    delete ui;
}

bool isDigitString(const QString& src)
{
    const char *s = src.toUtf8().data();
    while(*s && *s>='0' && *s<='9') s++;
    return !bool(*s);
}

void Config::on_pushButton_clicked()
{
    int OutputPipes = 0;
    if (ui->checkBox_out_1->isChecked()) OutputPipes++;
    if (ui->checkBox_out_2->isChecked()) OutputPipes++;
    if (ui->checkBox_out_3->isChecked()) OutputPipes++;
    if (ui->checkBox_out_4->isChecked()) OutputPipes++;
    if (ui->checkBox_out_5->isChecked()) OutputPipes++;
    if (ui->checkBox_out_6->isChecked()) OutputPipes++;
    if (ui->checkBox_out_7->isChecked()) OutputPipes++;
    if (ui->checkBox_out_8->isChecked()) OutputPipes++;
    if (OutputPipes != OutputPipesLimit) qDebug("Bug 1!");

    int InputPipes = 0;
    if (ui->checkBox_in_1->isChecked()) InputPipes++;
    if (ui->checkBox_in_2->isChecked()) InputPipes++;
    if (ui->checkBox_in_3->isChecked()) InputPipes++;
    if (ui->checkBox_in_4->isChecked()) InputPipes++;
    if (ui->checkBox_in_5->isChecked()) InputPipes++;
    if (ui->checkBox_in_6->isChecked()) InputPipes++;
    if (ui->checkBox_in_7->isChecked()) InputPipes++;
    if (ui->checkBox_in_8->isChecked()) InputPipes++;
    if (InputPipes != InputPipesLimit) qDebug("Bug 2!");

    bool isNumber;
    int size = ui->sizeEdit->text().toInt(&isNumber);
    if (isNumber == false) qDebug("Bug 3!");
    else if (size < SizeMinLimit) qDebug("Bug 4!");
    else if (size > SizeMaxLimit) qDebug("Bug 5!");
}
