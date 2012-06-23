#include "opencs.hpp"
#include "ui_opencs.h"

#include <QDebug>
#include <QFileDialog>

OpenCS::OpenCS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenCS)
{
    ui->setupUi(this);

    connect(ui->actionOpen,SIGNAL(triggered()), this, SLOT(openFile()));
}

OpenCS::~OpenCS()
{
    delete ui;
}

void OpenCS::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Esm"), "", tr("Esm Files (*.esm)"));

    try {
        qDebug() << "Trying to open esm:" << fileName;
        esm.open(fileName.toStdString());
        model = new ESMDataModel(esm);
        ui->treeView->setModel(model);
        ui->treeView->update();
    } catch(std::exception &e) {
        qWarning() << e.what();
    }
}
