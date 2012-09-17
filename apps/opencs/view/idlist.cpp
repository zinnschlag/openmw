#include "idlist.hpp"

#include "idlistitemdelegate.hpp"

#include <QDebug>
#include <QtGui>

QList<QStandardItem *> list;

IdList::IdList(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    mFilterProxyModel = new FilterProxyModel(this);

    IdlistItemDelegate *itemDelegate = new IdlistItemDelegate();
    //tableView->setItemDelegate(itemDelegate);

    tableView->setModel(mFilterProxyModel);
    tableView->verticalHeader()->setDefaultSectionSize(tableView->verticalHeader()->minimumSectionSize());
    tableView->horizontalHeader()->setMovable(true);
    tableView->horizontalHeader()->setStretchLastSection(false);

    connect(comboFilterRoot, SIGNAL(currentIndexChanged(int)), this, SLOT(filterRootChanged(int)));
}

IdList::~IdList()
{
}

void IdList::setModel(QAbstractItemModel *model)
{
    mFilterProxyModel->setSourceModel(model);
}

void IdList::setFilterModel(FilterEditModel *model)
{
    mModel = model;

    //FIXME This should work, bad workaround below
    //comboBox->setModel(model);
    //comboBox->setRootModelIndex(model->index(0, 0));
    int rows = model->rowCount(model->index(0, 0));
    for(int i=0; i< rows; i++) {

        QVariant data = model->data(model->index(0, 0).child(i, 0), Qt::DisplayRole);
        comboFilterRoot->addItem(data.toString());
    }

    mFilterProxyModel->setEditModel(model);
}

//TODO Make this nicer
void IdList::filterRootChanged(int row)
{
    //FIXME Hardcode
    mFilterProxyModel->setActiveFilter(mModel->index(0, 0).child(row, 0));
}
