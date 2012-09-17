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

void IdList::setFilterModel(FilterEditModel *editModel)
{
    comboFilterRoot->setModel(editModel);

    mFilterProxyModel->setEditModel(editModel);
}

//TODO Make this nicer
void IdList::filterRootChanged(int row)
{
    FilterEditModel* editModel = dynamic_cast<FilterEditModel*>(comboFilterRoot->model());
    if(editModel) {

        mFilterProxyModel->setActiveFilter(editModel->index(row, 0));
    }

    mFilterProxyModel->sourceModel();
}
