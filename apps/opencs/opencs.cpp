#include "opencs.hpp"
#include "ui_opencs.h"

#include <QDebug>
#include <QProcessEnvironment>

#include <QFileDialog>
#include <QDockWidget>

#include <QUndoView>

#include "model/modelitem.hpp"


#include "view/filter/filtertree.hpp"
#include "view/filter/filtereditor.hpp"

OpenCS::OpenCS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenCS)
{
    ui->setupUi(this);

    setDockOptions(QMainWindow::AllowNestedDocks | QMainWindow::AllowTabbedDocks);
    setCentralWidget(NULL);

    connect(ui->actionOpen,SIGNAL(triggered()), this, SLOT(openFile()));

    // Create Viewmodel
    mModel = new DataModel(this);
    mModel->loadGuiData();
    mModel->loadFilterDirectory(":/filter/");

    updateComponents();

    //TODO
    //connect(filterTree, SIGNAL(indexSelected(QModelIndex)), filterEditor, SLOT(setCurrentModelIndex(QModelIndex)));
}

OpenCS::~OpenCS()
{
    delete ui;
}

void OpenCS::updateComponents()
{
    //FIXME hardcoded model index
    QModelIndex guiParentIndex = mModel->index(2, 0);

    int count = mModel->rowCount(guiParentIndex);
    for(int i=0; i<count; i++) {
        ModelItem* baseItem = static_cast<ModelItem*>(guiParentIndex.child(i, 0).internalPointer());

        WidgetItem* item = dynamic_cast<WidgetItem*>(baseItem);
        if(!item)
            continue;


        QDockWidget *idListDock = new QDockWidget(item->title(), this);
        idListDock->setFeatures(QDockWidget::AllDockWidgetFeatures);

        QWidget* innerWidget;
        if(item->typeName() == "IdList") {
            IdList* idList = new IdList(this);
            idList->setFilterModel(mModel);

            innerWidget = idList;
        } else if(item->typeName() == "FilterTree") {
            FilterTree* filterTree = new FilterTree(this);
            filterTree->setModel(mModel);

            innerWidget = filterTree;
        } else if(item->typeName() == "FilterEditor") {
            FilterEditor* filterEditor = new FilterEditor(this);
            filterEditor->setModel(mModel);

            innerWidget = filterEditor;
        } else if(item->typeName() == "UndoRedo") {
            QUndoView *undoView = new QUndoView(this);
            //undoView->setStack(filterModel->undoStack());

            innerWidget = undoView;
        } else if(item->typeName() == "ItemModel") {
            QTreeView *itemModelTreeView = new QTreeView(this);
            itemModelTreeView->setModel(mModel);
            itemModelTreeView->setColumnWidth(0, 500);
            //itemModelTreeView->resizeColumnToContents(0);

            innerWidget = itemModelTreeView;
        }

        idListDock->setWidget(innerWidget);

        addDockWidget(item->area(), idListDock);
    }
}

void OpenCS::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Esm"), "", tr("Esm Files (*.esm)"));
    if (!fileName.isEmpty())
    {
        mModel->loadEsmFile(fileName);
    }
}
