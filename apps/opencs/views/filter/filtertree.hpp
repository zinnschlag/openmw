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

private:
    Ui::FilterTree *ui;
};

#endif
