#ifndef IDLIST_HPP
#define IDLIST_HPP

#include "ui_idlist.h"

#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

#include "../viewmodel/esmdatamodel.hpp"
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

    void setFilterModel(FilterEditModel *model);

private:
    FilterEditModel *mDataModel;

    ESMDataModel *mViewModel;
    FilterProxyModel *mFilterProxyModel;

private slots:
    void rowsInserted(const QModelIndex & parent, int start, int end);

    void filterRootChanged(int row);
    void sourceChanged(int row);
};

#endif
