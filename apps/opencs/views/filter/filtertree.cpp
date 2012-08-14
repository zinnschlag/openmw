#include "filtertree.hpp"
#include "ui_filtertree.h"

#include "../idlistfilter.hpp"

FilterTree::FilterTree(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::FilterTree)
{
    ui->setupUi(this);
}

FilterTree::~FilterTree()
{
}

void FilterTree::setModel(FilterEditModel *model)
{
    ui->treeViewFilter->setModel(model);
    ui->treeViewFilter->header()->setResizeMode(QHeaderView::ResizeToContents);
}
