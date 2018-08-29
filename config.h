#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>
#include "mainwindow.h"
#include <QDoubleValidator>
#include <QIntValidator>

namespace Ui {
class Config;
}

class Config : public QDialog
{
    Q_OBJECT

public:
    explicit Config(int inflow0, int inflow1, int random, QWidget *parent = 0);
    ~Config();

signals:
    void finished(int, int, int);

private slots:
	void finish();

private:
    Ui::Config *ui;
    QIntValidator *inputLimit, *randomLimit;
};

#endif // CONFIG_H
