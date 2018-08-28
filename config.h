#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>

#define InputPipesLimit 2
#define OutputPipesLimit 3
#define SizeMinLimit 5
#define SizeMaxLimit 8

namespace Ui {
class Config;
}

class Config : public QDialog
{
    Q_OBJECT

public:
    explicit Config(QWidget *parent = 0);
    ~Config();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Config *ui;
};

#endif // CONFIG_H
