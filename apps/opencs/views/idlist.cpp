#include "idlist.hpp"
#include "ui_idlist.h"

#include <QDebug>
#include <QtGui>

QList<QStandardItem *> list;

IdList::IdList(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::IdList)
{
    ui->setupUi(this);

    mSortModel = new QSortFilterProxyModel(this);

    mSortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    mSortModel->setFilterKeyColumn(-1);

    ui->treeView->setSortingEnabled(true);
}

IdList::~IdList()
{
    delete ui;
}

void IdList::setModel(QAbstractItemModel *model)
{
    mSortModel->setSourceModel(model);
    ui->treeView->setModel(mSortModel);

    //ui->treeView->header()->setSectionHidden(0, true);
    ui->treeView->header()->setResizeMode(QHeaderView::ResizeToContents);
}

void IdList::on_lineEdit_textEdited(const QString &arg1)
{
    mSortModel->setFilterWildcard(arg1);
}
