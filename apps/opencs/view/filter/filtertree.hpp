#ifndef FILTERTREE_HPP
#define FILTERTREE_HPP

#include "ui_filtertree.h"

#include "../../viewmodel/datamodel.hpp"

#include <QIdentityProxyModel>

class SimpleTreeProxyModel : public QIdentityProxyModel
{
public :
    explicit SimpleTreeProxyModel(QObject* parent = 0) : QIdentityProxyModel(parent){}

    int columnCount(const QModelIndex &parent) const
    {
        return 1;
    }
};

namespace Ui
{
    class FilterTree;
}

class FilterTree : public QWidget, private Ui::FilterTree
{
    Q_OBJECT

public:
    explicit FilterTree(QWidget *parent = 0);
    ~FilterTree();

    void setModel(DataModel *model);

signals:
    void indexSelected(const QModelIndex& index);

private:
    DataModel *mModel;
    SimpleTreeProxyModel *mSimpleModel;

    QModelIndex mContextMenuModelIndex;

private slots:
    void rootItemIndexChanged(int index);

    void clicked(const QModelIndex & index);
    void contextMenu(const QPoint& point);

    void contextMenuActionTriggered();
};

#endif
