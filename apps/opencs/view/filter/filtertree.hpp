#ifndef FILTERTREE_HPP
#define FILTERTREE_HPP

#include "ui_filtertree.h"

#include "../../viewmodel/filtereditmodel.hpp"

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

    void setModel(FilterEditModel *model);

    QSize sizeHint() const;

signals:
    void indexSelected(const QModelIndex& index);

private:
    FilterEditModel *mModel;

    QModelIndex mContextMenuModelIndex;

private slots:
    void clicked(const QModelIndex & index);
    void contextMenu(const QPoint& point);

    void deleteFilter();
    void addUnionFilter();
    void addMatchFilter();
};

#endif
