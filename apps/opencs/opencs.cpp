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
    connect(ui->actionAddIdList, SIGNAL(triggered()), this, SLOT(addIdList()));

    model = new ESMDataModel(this);

    addIdList();
}

OpenCS::~OpenCS()
{
    delete ui;
}

void OpenCS::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Esm"), "", tr("Esm Files (*.esm)"));
    if (!fileName.isEmpty())
    {
        model->loadEsmFile(fileName);
    }
}

void OpenCS::addIdList()
{
    IdList *idList = new IdList(this);
    idList->setModel(model);
    this->addDockWidget(Qt::TopDockWidgetArea, idList);
}
