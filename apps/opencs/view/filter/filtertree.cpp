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

    QStringList actionIds = mModel->data(index, FilterEditModel::ItemCommandsRole).toStringList();

    foreach(QString actionId, actionIds) {
        if(actionId == "-") {
            menu->addSeparator();
        } else {
            QAction *openAct = new QAction(actionId, this);
            openAct->setData(actionId);
            connect(openAct, SIGNAL(triggered()), this, SLOT(contextMenuActionTriggered()));
            menu->addAction(openAct);
        }
    }

    menu->exec(treeViewFilter->mapToGlobal(point));
}

void FilterTree::contextMenuActionTriggered()
{
    QAction *action = qobject_cast<QAction*>(QObject::sender());
    if(action) {
        mModel->executeCommand(action->data().toString(), mContextMenuModelIndex);
    }
}

