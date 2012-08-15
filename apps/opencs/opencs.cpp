#include "opencs.hpp"
#include "ui_opencs.h"

#include <QDebug>
#include <QFileDialog>

#include "esmdatamodel.hpp"


#include "views/filter/filtertree.hpp"
#include "views/filter/filtereditor.hpp"

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

    FilterEditModel *filterModel = new FilterEditModel(this);
    filterModel->load();

    idList = new IdList(this);
    idList->setModel(model);
    idList->setFilterModel(filterModel);
    this->addDockWidget(Qt::RightDockWidgetArea, idList);

    FilterTree *filterTree = new FilterTree(this);
    filterTree->setModel(filterModel);
    this->addDockWidget(Qt::LeftDockWidgetArea, filterTree);

    FilterEditor *filterEditor = new FilterEditor(this);
    this->addDockWidget(Qt::LeftDockWidgetArea, filterEditor);

    connect(filterTree, SIGNAL(filterSelected(Filter*)), filterEditor, SLOT(editFilter(Filter*)));
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

        idList->loadColumnConfig();
    }
}

void OpenCS::addIdList()
{
    IdList *idList = new IdList(this);
    idList->setModel(model);
    this->addDockWidget(Qt::RightDockWidgetArea, idList);
}
