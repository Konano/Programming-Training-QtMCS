#include "config.h"
#include "ui_config.h"
#include <QMessageBox>

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
    QString error;

    bool isNumber;
    int size = ui->sizeEdit->text().toInt(&isNumber);
    if (isNumber == false)
    {
        if (!error.isEmpty()) error += tr("\n");
        error += tr("芯片大小输入有误");
    }
    else if (size < SizeMinLimit)
    {
        if (!error.isEmpty()) error += tr("\n");
        error += tr("芯片大小小于") + QString::number(SizeMinLimit);
    }
    else if (size > SizeMaxLimit)
    {
        if (!error.isEmpty()) error += tr("\n");
        error += tr("芯片大小大于") + QString::number(SizeMaxLimit);
    }

    int InputPipes = 0; bool Input[8];
    if (Input[0] = ui->checkBox_in_0->isChecked()) InputPipes++;
    if (Input[1] = ui->checkBox_in_1->isChecked()) InputPipes++;
    if (Input[2] = ui->checkBox_in_2->isChecked()) InputPipes++;
    if (Input[3] = ui->checkBox_in_3->isChecked()) InputPipes++;
    if (Input[4] = ui->checkBox_in_4->isChecked()) InputPipes++;
    if (Input[5] = ui->checkBox_in_5->isChecked()) InputPipes++;
    if (Input[6] = ui->checkBox_in_6->isChecked()) InputPipes++;
    if (Input[7] = ui->checkBox_in_7->isChecked()) InputPipes++;
    if (InputPipes != InputPipesLimit)
    {
        if (!error.isEmpty()) error += tr("\n");
        error += tr("输入管道数量不为") + QString::number(InputPipesLimit);
    }

    int OutputPipes = 0; bool Output[8];
    if (Output[0] = ui->checkBox_out_0->isChecked()) OutputPipes++;
    if (Output[1] = ui->checkBox_out_1->isChecked()) OutputPipes++;
    if (Output[2] = ui->checkBox_out_2->isChecked()) OutputPipes++;
    if (Output[3] = ui->checkBox_out_3->isChecked()) OutputPipes++;
    if (Output[4] = ui->checkBox_out_4->isChecked()) OutputPipes++;
    if (Output[5] = ui->checkBox_out_5->isChecked()) OutputPipes++;
    if (Output[6] = ui->checkBox_out_6->isChecked()) OutputPipes++;
    if (Output[7] = ui->checkBox_out_7->isChecked()) OutputPipes++;
    if (OutputPipes != OutputPipesLimit)
    {
        if (!error.isEmpty()) error += tr("\n");
        error += tr("输出管道数量不为") + QString::number(OutputPipesLimit);
    }

    if (!error.isEmpty())
    {
        QMessageBox::warning(this, tr("Error"), error, QMessageBox::Yes);
    }
    else
    {
        emit finish(size, Input, Output);
        accept();
    }
}
