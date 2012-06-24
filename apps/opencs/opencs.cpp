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
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(selectObject(QModelIndex)));

//    variantManager = new QtVariantPropertyManager(this);
//    variantFactory = new QtVariantEditorFactory(this);
//    variantEditor = new QtTreePropertyBrowser(this);

//    variantEditor->setFactoryForManager(variantManager, variantFactory);
//    variantEditor->setPropertiesWithoutValueMarked(true);
//    variantEditor->setRootIsDecorated(false);

//    ui->horizontalLayout->addWidget(variantEditor);

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

        ui->treeView->setModel(model);
        ui->treeView_2->setModel(model);

    } catch(std::exception &e) {
        qWarning() << e.what();
    }
}


void OpenCS::selectObject(const QModelIndex &index)
{
//    ESMDataItem *item = static_cast<ESMDataItem*>(index.internalPointer());
//    variantEditor->clear();
//    QtProperty *topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), QLatin1String(" TOP"));
//    for(int i=0; i<item->columnCount(); i++) {
//        QVariant val = item->data(i);
//        QtVariantProperty *item = variantManager->addProperty(val.type(), QString::number(i) + QLatin1String("Property"));
//        item->setValue(val);
//        //item->setValue(true);
//        topItem->addSubProperty(item);
//    }
//    variantEditor->addProperty(topItem);
}



