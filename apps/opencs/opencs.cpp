#include "opencs.hpp"
#include "ui_opencs.h"

#include <QDebug>
#include <QProcessEnvironment>

#include <QFileDialog>
#include <QDockWidget>

#include <QUndoView>

#include "model/modelitem.hpp"

#include "persistence/esmserializer.hpp"

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


    // Create Data Model
    mRootItem = new ModelItem();

    {
        ModelItem* filterParentItem = new ModelItem("filter", mRootItem);

        FilterDom *filterDom = new FilterDom(this);
        QDir filterDirectory(":/filter/");
        foreach(QString filterFileName, filterDirectory.entryList())
        {
            QString filterFilePath = filterDirectory.absoluteFilePath(filterFileName);

            filterParentItem->appendChild(filterDom->loadFile(filterFilePath, filterParentItem));
        }

        mRootItem->appendChild(filterParentItem);
    }

    esmFilesParent = new ModelItem("esm", mRootItem);
    mRootItem->appendChild(esmFilesParent);

    // Create Viewmodel
    mModel = new DataModel(mRootItem, this);


    QList<WidgetItem*> widgetItems;

    WidgetItem* element;

    element = new IdListWidgetItem(mRootItem);
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
        item->setModel(mModel);
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

void OpenCS::loadProject()
{
}

void OpenCS::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Esm"), "", tr("Esm Files (*.esm)"));
    if (!fileName.isEmpty())
    {
        EsmFile *esmFile = new EsmFile(fileName, esmFilesParent);

        EsmSerializer *serializer = new EsmSerializer(this);
        serializer->load(esmFile);

        mModel->emitBeginInsertRows(mModel->index(1, 0), mModel->rowCount(), mModel->rowCount() + 1);
        esmFilesParent->appendChild(esmFile);
        mModel->emitEndInsertRows();
    }
}
