#include "filtertree.hpp"
#include "ui_filtertree.h"

#include "../idlistfilter.hpp"

FilterTree::FilterTree(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::FilterTree)
{
    ui->setupUi(this);

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
