#include "filtertree.hpp"

#include <QMenu>

FilterTree::FilterTree(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    treeViewFilter->header()->hide();

    connect(treeViewFilter, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu(QPoint)));
    connect(treeViewFilter, SIGNAL(clicked(QModelIndex)), this, SLOT(clicked(QModelIndex)));
}

FilterTree::~FilterTree()
{
}

void FilterTree::setModel(FilterEditModel *model)
{
    mModel = model;

    treeViewFilter->setModel(mModel);
    treeViewFilter->header()->setResizeMode(QHeaderView::ResizeToContents);

    //resize(sizeHint());
}

QSize FilterTree::sizeHint() const
{
    return QSize(200, 200);
}

void FilterTree::clicked(const QModelIndex &index)
{
    emit indexSelected(index);
}

void FilterTree::contextMenu(const QPoint &point)
{
    QModelIndex index = treeViewFilter->indexAt(point);
    if(!index.isValid())
        return;

    mContextMenuModelIndex = index;

    QMenu *menu = new QMenu;

    Filter *filter = static_cast<Filter*>(index.internalPointer());
    FilterList* filterList = dynamic_cast<FilterList*>(filter);
    if (filterList)
    {
        menu->addAction(QString("Add Union"), this, SLOT(addUnionFilter()));
        menu->addAction(QString("Add Match"), this, SLOT(addMatchFilter()));
        menu->addSeparator();
    }

    menu->addAction(QString("Delete"), this, SLOT(deleteFilter()));
    menu->exec(treeViewFilter->mapToGlobal(point));
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
