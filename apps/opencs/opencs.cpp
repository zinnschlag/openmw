#include "opencs.hpp"
#include "ui_opencs.h"

#include <QDebug>
#include <QFileDialog>

#include "esmdatamodel.hpp"

#include "views/idlist.hpp"

OpenCS::OpenCS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenCS)
{
    ui->setupUi(this);

    setDockOptions(QMainWindow::AllowNestedDocks | QMainWindow::AllowTabbedDocks);
    setCentralWidget(NULL);

    connect(ui->actionOpen,SIGNAL(triggered()), this, SLOT(openFile()));

    esm.setEncoding("default");
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
        std::string stdStrFileName = fileName.toStdString();
        esm.open(stdStrFileName);
        model = new ESMDataModel(esm);

        IdList *idList = new IdList(this);
        idList->setModel(model);
        this->addDockWidget(Qt::TopDockWidgetArea, idList);
    } catch(std::exception &e) {
        qWarning() << e.what();
    }
}
