#include "idlist.hpp"

#include "idlistitemdelegate.hpp"

#include <QDebug>
#include <QtGui>

QList<QStandardItem *> list;

IdList::IdList(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    mViewModel = new ESMDataModel(this);

    mFilterProxyModel = new FilterProxyModel(this);
    mFilterProxyModel->setSourceModel(mViewModel);

    // TODO
    //IdlistItemDelegate *itemDelegate = new IdlistItemDelegate();
    //tableView->setItemDelegate(itemDelegate);

    tableView->setModel(mFilterProxyModel);
    tableView->verticalHeader()->setDefaultSectionSize(tableView->verticalHeader()->minimumSectionSize());
    tableView->horizontalHeader()->setMovable(true);
    tableView->horizontalHeader()->setStretchLastSection(false);

    connect(comboFilterRoot, SIGNAL(currentIndexChanged(int)), this, SLOT(filterRootChanged(int)));

    connect(comboSource, SIGNAL(currentIndexChanged(int)), this, SLOT(sourceChanged(int)));
}

IdList::~IdList()
{
}

void IdList::setFilterModel(FilterEditModel *model)
{
    mDataModel = model;

    connect(mDataModel, SIGNAL(rowsInserted(QModelIndex,int,int)),
              this,   SLOT(rowsInserted(QModelIndex,int,int)));

    //FIXME This should work, bad workaround below
    //comboBox->setModel(model);
    //comboBox->setRootModelIndex(model->index(0, 0));
    int rows = model->rowCount(model->index(0, 0));
    for(int i=0; i< rows; i++) {

        QVariant data = model->data(model->index(0, 0).child(i, 0), Qt::DisplayRole);
        comboFilterRoot->addItem(data.toString());
    }
    comboFilterRoot->adjustSize();


    mFilterProxyModel->setEditModel(model);
}

//TODO Make this nicer
void IdList::filterRootChanged(int row)
{
    //FIXME hardcoded index
    mFilterProxyModel->setActiveFilter(mDataModel->index(0, 0).child(row, 0));
}

void IdList::sourceChanged(int row)
{
    //FIXME hardcoded index and internal pointer usage
    ModelItem* item = static_cast<ModelItem*>(mDataModel->index(1, 0).child(row, 0).internalPointer());
    if(!item)
        return;

    mViewModel->setRootItem(item);

    mFilterProxyModel->setSourceModel(mViewModel);
}


void IdList::rowsInserted(const QModelIndex &parent, int start, int end)
{
    comboSource->clear();
    //FIXME Copy-Paste
    int rows2 = mDataModel->rowCount(mDataModel->index(1, 0));
    for(int i=0; i< rows2; i++) {

        QVariant data = mDataModel->data(mDataModel->index(1, 0).child(i, 0), Qt::DisplayRole);
        comboSource->addItem(data.toString());
    }
}
