#include "inside.h"
#include "ui_inside.h"

Inside::Inside(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Inside)
{
    ui->setupUi(this);
}

Inside::~Inside()
{
    delete ui;
}
