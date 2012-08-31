#include "filtertree.hpp"

#include <QMenu>

FilterTree::FilterTree(QWidget *parent)
    : QWidget(parent)
    , mSimpleView(true)
{
    setupUi(this);

    treeViewFilter->header()->hide();

    connect(treeViewFilter, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu(QPoint)));
    connect(treeViewFilter, SIGNAL(clicked(QModelIndex)), this, SLOT(clicked(QModelIndex)));

    mSimpleModel = new SimpleTreeProxyModel(this);

    //mSimpleView = false;
}

FilterTree::~FilterTree()
{
}

void FilterTree::setModel(FilterEditModel *model)
{
    mModel = model;
    mSimpleModel->setSourceModel(mModel);

    if(mSimpleView)
        treeViewFilter->setModel(mSimpleModel);
    else
        treeViewFilter->setModel(mModel);

    treeViewFilter->header()->setResizeMode(QHeaderView::ResizeToContents);
}

void FilterTree::clicked(const QModelIndex &index)
{
    QModelIndex res;

    if(mSimpleView)
        res = mSimpleModel->mapToSource(index);
    else
        res = index;

    emit indexSelected(res);
}

void FilterTree::contextMenu(const QPoint &point)
{
    QModelIndex index = treeViewFilter->indexAt(point);
    if(!index.isValid())
        return;

    if(mSimpleView)
        index = mSimpleModel->mapToSource(index);

    mContextMenuModelIndex = index;

    QMenu *menu = new QMenu;

    QStringList actionIds = mModel->data(index, FilterEditModel::ItemCommandsRole).toStringList();
    QVariantList params = mModel->data(index, FilterEditModel::ItemParamsRole).toList();

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

