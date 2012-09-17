#ifndef IDLIST_HPP
#define IDLIST_HPP

#include "ui_idlist.h"

#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

#include "../viewmodel/filtereditmodel.hpp"
#include "../viewmodel/filterproxymodel.hpp"

namespace Ui
{
class IdList;
}

class IdList : public QWidget, private Ui::IdList
{
    Q_OBJECT
    
public:
    explicit IdList(QWidget *parent = 0);
    ~IdList();
    
    void setModel(QAbstractItemModel *model);
    void setFilterModel(FilterEditModel *model);

    void loadColumnConfig();

private:
    QAbstractItemModel *mModel;
    FilterProxyModel *mFilterProxyModel;

private slots:
    void filterRootChanged(int row);
};

#endif
