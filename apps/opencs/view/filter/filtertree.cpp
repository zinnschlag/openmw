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

    mContextMenuModelIndex = index;

    QMenu *menu = new QMenu;

    QStringList actionIds = mModel->data(index, DataModel::ItemCommandsRole).toStringList();
    QVariantList params = mModel->data(index, DataModel::ItemParamsRole).toList();

    int i=0;
    foreach(QString actionId, actionIds) {
        if(actionId == "-") {
            menu->addSeparator();
        } else {
            QString name = actionId + " " + params[i].toString();
            QAction *openAct = new QAction(name, this);
            openAct->setProperty("Command", actionId);
            openAct->setProperty("Param", params[i]);

            connect(openAct, SIGNAL(triggered()), this, SLOT(contextMenuActionTriggered()));
            menu->addAction(openAct);
        }

        i++;
    }

    menu->exec(treeViewFilter->mapToGlobal(point));
}

void FilterTree::contextMenuActionTriggered()
{
    QAction *action = qobject_cast<QAction*>(QObject::sender());
    if(action) {
        mModel->executeCommand(mContextMenuModelIndex, action->property("Command").toString(), action->property("Param"));
    }
}




