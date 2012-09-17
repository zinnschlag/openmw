#include "opencs.hpp"
#include "ui_opencs.h"

#include <QDebug>
#include <QProcessEnvironment>

#include <QFileDialog>
#include <QDockWidget>

#include <QUndoView>

#include "model/modelitem.hpp"

#include "viewmodel/esmdatamodel.hpp"


#include "view/filter/filtertree.hpp"
#include "view/filter/filtereditor.hpp"




OpenCS::OpenCS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenCS)
{
    ui->setupUi(this);

    mRootItem = new ModelItem();

    setDockOptions(QMainWindow::AllowNestedDocks | QMainWindow::AllowTabbedDocks);
    setCentralWidget(NULL);

    connect(ui->actionOpen,SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionAddIdList, SIGNAL(triggered()), this, SLOT(addIdList()));

    model = new ESMDataModel(this);


    FilterEditModel *filterModel = new FilterEditModel(mRootItem, this);



    QList<WidgetItem*> widgetItems;

    WidgetItem* element;

    element = new IdListWidgetItem(model, mRootItem);
    element->setDockArea(Qt::RightDockWidgetArea);
    widgetItems.append(element);

    element = new FilterTreeWidgetItem(mRootItem);
    element->setDockArea(Qt::LeftDockWidgetArea);
    widgetItems.append(element);

    element = new FilterEditorWidgetItem(mRootItem);
    element->setDockArea(Qt::LeftDockWidgetArea);
    widgetItems.append(element);

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    if(env.contains("OPENCS_DEBUG_GUI")) {
        element = new UndoRedoWidgetItem(mRootItem);
        element->setDockArea(Qt::LeftDockWidgetArea);
        widgetItems.append(element);

        element = new ItemModelWidgetItem(mRootItem);
        element->setDockArea(Qt::BottomDockWidgetArea);
        widgetItems.append(element);
    }

    foreach(WidgetItem* item, widgetItems) {
        item->setModel(filterModel);
        item->addWidget(this);
    }

    //TODO
    //connect(filterTree, SIGNAL(indexSelected(QModelIndex)), filterEditor, SLOT(setCurrentModelIndex(QModelIndex)));
}

OpenCS::~OpenCS()
{
    delete ui;
    delete mRootItem;
}

void OpenCS::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Esm"), "", tr("Esm Files (*.esm)"));
    if (!fileName.isEmpty())
    {
        model->loadEsmFile(fileName);
    }
}
