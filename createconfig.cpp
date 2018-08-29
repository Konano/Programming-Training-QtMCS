#include "createconfig.h"
#include "ui_createconfig.h"
#include <QMessageBox>

CreateConfig::CreateConfig(int size, bool *input, bool *output, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateConfig)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    inCheckBox[0] = ui->checkBox_in_0;
    inCheckBox[1] = ui->checkBox_in_1;
    inCheckBox[2] = ui->checkBox_in_2;
    inCheckBox[3] = ui->checkBox_in_3;
    inCheckBox[4] = ui->checkBox_in_4;
    inCheckBox[5] = ui->checkBox_in_5;
    inCheckBox[6] = ui->checkBox_in_6;
    inCheckBox[7] = ui->checkBox_in_7;

    outCheckBox[0] = ui->checkBox_out_0;
    outCheckBox[1] = ui->checkBox_out_1;
    outCheckBox[2] = ui->checkBox_out_2;
    outCheckBox[3] = ui->checkBox_out_3;
    outCheckBox[4] = ui->checkBox_out_4;
    outCheckBox[5] = ui->checkBox_out_5;
    outCheckBox[6] = ui->checkBox_out_6;
    outCheckBox[7] = ui->checkBox_out_7;

    ui->sizeBox->setCurrentIndex(size-SizeMinLimit);
    checkBoxEnableChange(size);

    for(int i=0; i<size; i++) if (input[i]) inCheckBox[i]->setChecked(true);
    for(int i=0; i<size; i++) if (output[i]) outCheckBox[i]->setChecked(true);
}

CreateConfig::~CreateConfig()
{
    delete ui;
    for(int i=0; i<8; i++) delete inCheckBox[i];
    for(int i=0; i<8; i++) delete outCheckBox[i];
}

void CreateConfig::checkBoxEnableChange(int size)
{
    for(int i=0; i<8; i++)
        if (i<size)
        {
            inCheckBox[i]->setEnabled(true);
            outCheckBox[i]->setEnabled(true);
        }
        else
        {
            inCheckBox[i]->setChecked(false);
            inCheckBox[i]->setEnabled(false);
            outCheckBox[i]->setChecked(false);
            outCheckBox[i]->setEnabled(false);
        }
}
void CreateConfig::on_sizeBox_currentIndexChanged(int index)
{
    checkBoxEnableChange(index+SizeMinLimit);
}

void CreateConfig::on_buttonBox_accepted()
{
    QString error;

    int size = ui->sizeBox->currentIndex()+SizeMinLimit;

    int InputPipes = 0; bool Input[size];
    for(int i=0; i<size; i++) if (Input[i] = inCheckBox[i]->isChecked()) InputPipes++;
    if (InputPipes != InputPipesLimit)
    {
        if (!error.isEmpty()) error += tr("\n");
        error += tr("输入管道数量不为") + QString::number(InputPipesLimit);
    }

    int OutputPipes = 0; bool Output[size];
    for(int i=0; i<size; i++) if (Output[i] = outCheckBox[i]->isChecked()) OutputPipes++;
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
        emit finished(size, Input, Output);
        accept();
    }
}
