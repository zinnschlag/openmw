#include "idlist.hpp"
#include "ui_idlist.h"

#include "idlistitemdelegate.hpp"

#include <QDebug>
#include <QtGui>

QList<QStandardItem *> list;

IdList::IdList(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::IdList)
{
    ui->setupUi(this);

    FilterEditModel *editModel = new FilterEditModel(this);
    editModel->load();

    mFilterProxyModel = new FilterProxyModel(this);
    mFilterProxyModel->setEditModel(editModel);

    IdlistItemDelegate *itemDelegate = new IdlistItemDelegate();
    ui->tableView->setItemDelegate(itemDelegate);

    ui->tableView->setModel(mFilterProxyModel);
    ui->tableView->verticalHeader()->setDefaultSectionSize(ui->tableView->verticalHeader()->minimumSectionSize());
    ui->tableView->horizontalHeader()->setMovable(true);
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Interactive);

    ui->treeViewFilter->setModel(editModel);
    ui->treeViewFilter->header()->setResizeMode(QHeaderView::ResizeToContents);
}

IdList::~IdList()
{
    delete ui;
}

void IdList::setModel(QAbstractItemModel *model)
{
    mFilterProxyModel->setSourceModel(model);
}
