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

