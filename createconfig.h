#ifndef CREATECONFIG_H
#define CREATECONFIG_H

#include <QDialog>
#include <QCheckBox>
#include <QDebug>

#define InputPipesLimit 2
#define OutputPipesLimit 3
#define SizeMinLimit 5
#define SizeMaxLimit 8

namespace Ui {
class CreateConfig;
}

class CreateConfig : public QDialog
{
    Q_OBJECT

public:
    explicit CreateConfig(int size, bool *input, bool *output, QWidget *parent = 0);
    ~CreateConfig();

signals:
    void finished(int,bool*,bool*);

private slots:
    void on_sizeBox_currentIndexChanged(int index);

    void on_buttonBox_accepted();

private:
    Ui::CreateConfig *ui;
    QCheckBox *inCheckBox[8], *outCheckBox[8];

    void checkBoxEnableChange(int size);
};

#endif // CREATECONFIG_H
