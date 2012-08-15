#include "filtertree.hpp"
#include "ui_filtertree.h"

#include "../idlistfilter.hpp"

#include <QMenu>

FilterTree::FilterTree(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::FilterTree)
{
    ui->setupUi(this);

    connect(this->ui->treeViewFilter, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu(QPoint)));
    connect(this->ui->treeViewFilter, SIGNAL(clicked(QModelIndex)), this, SLOT(clicked(QModelIndex)));
}

FilterTree::~FilterTree()
{
}

void FilterTree::setModel(FilterEditModel *model)
{
    mModel = model;

    ui->treeViewFilter->setModel(mModel);
    ui->treeViewFilter->header()->setResizeMode(QHeaderView::ResizeToContents);
}

void FilterTree::clicked(const QModelIndex &index)
{
    Filter *filter = static_cast<Filter*>(index.internalPointer());
    emit filterSelected(filter);
}

void FilterTree::contextMenu(const QPoint &point)
{
    QModelIndex index = this->ui->treeViewFilter->indexAt(point);
    if(!index.isValid())
        return;

    mContextMenuModelIndex = index;



    QMenu *menu = new QMenu;

    Filter *filter = static_cast<Filter*>(index.internalPointer());
    UnionFilter* unionFilter = dynamic_cast<UnionFilter*>(filter);
    if (unionFilter)
    {
        menu->addAction(QString("Add Union"), this, SLOT(addUnionFilter()));
        menu->addAction(QString("Add Match"), this, SLOT(addMatchFilter()));
        menu->addSeparator();
    }


    menu->addAction(QString("Delete"), this, SLOT(deleteFilter()));
    menu->exec(this->ui->treeViewFilter->mapToGlobal(point));
}

void FilterTree::deleteFilter()
{
    mModel->removeRow(mContextMenuModelIndex.row(), mContextMenuModelIndex.parent());
}

void FilterTree::addUnionFilter()
{
    mModel->addUnionFilter(mContextMenuModelIndex);
}

void FilterTree::addMatchFilter()
{
    mModel->addMatchFilter(mContextMenuModelIndex);
}
