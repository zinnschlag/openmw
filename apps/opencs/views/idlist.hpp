#ifndef IDLIST_HPP
#define IDLIST_HPP

#include <QDockWidget>

#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

#include "idlistfilter.hpp"

namespace Ui
{
class IdList;
}

class IdList : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit IdList(QWidget *parent = 0);
    ~IdList();
    
    void setModel(QAbstractItemModel *model);
    void setFilterModel(FilterEditModel *editModel);

private:
    Ui::IdList *ui;

    FilterProxyModel *mFilterProxyModel;
};

#endif
