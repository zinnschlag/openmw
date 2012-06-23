#include "opencs.hpp"
#include "ui_opencs.h"

OpenCS::OpenCS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenCS)
{
    ui->setupUi(this);
}

OpenCS::~OpenCS()
{
    delete ui;
}
