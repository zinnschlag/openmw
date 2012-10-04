#include "filtertree.hpp"

#include <QMenu>
#include <QListView>

FilterTree::FilterTree(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    treeViewFilter->header()->hide();

    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(rootItemIndexChanged(int)));
    connect(treeViewFilter, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu(QPoint)));
    connect(treeViewFilter, SIGNAL(clicked(QModelIndex)), this, SLOT(clicked(QModelIndex)));

    mSimpleModel = new SimpleTreeProxyModel(this);
}

FilterTree::~FilterTree()
{
}

void FilterTree::setModel(DataModel *model)
{
    mModel = model;

    //FIXME This should work, bad workaround below
    //comboBox->setModel(model);
    //comboBox->setRootModelIndex(model->index(0, 0));
    int rows = model->rowCount(model->index(0, 0));
    for(int i=0; i< rows; i++) {

        QVariant data = model->data(model->index(0, 0).child(i, 0), Qt::DisplayRole);
        comboBox->addItem(data.toString());
    }
}

void FilterTree::rootItemIndexChanged(int index)
{
    mSimpleModel->setSourceModel(mModel);
    treeViewFilter->setModel(mSimpleModel);

    //FIXME Hardcode
    treeViewFilter->setRootIndex(mSimpleModel->index(0, 0).child(index, 0));

    treeViewFilter->header()->setResizeMode(QHeaderView::ResizeToContents);
    treeViewFilter->expandAll();
}

void FilterTree::clicked(const QModelIndex &index)
{
    QModelIndex res;

    res = mSimpleModel->mapToSource(index);

    emit indexSelected(res);
}

void FilterTree::contextMenu(const QPoint &point)
{
    QModelIndex index = treeViewFilter->indexAt(point);
    if(!index.isValid())
        return;

    index = mSimpleModel->mapToSource(index);

    QMenu *menu = new QMenu;

    mModel->fillContextMenu(menu, index);

    menu->exec(treeViewFilter->mapToGlobal(point));
}
