#ifndef FILTERTREE_HPP
#define FILTERTREE_HPP

#include <QDockWidget>

#include "../idlistfilter.hpp"

namespace Ui
{
    class FilterTree;
}

class FilterTree : public QDockWidget
{
    Q_OBJECT

public:
    explicit FilterTree(QWidget *parent = 0);
    ~FilterTree();

    void setModel(FilterEditModel *model);

signals:
    void filterSelected(Filter* filter);

private:
    Ui::FilterTree *ui;
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
