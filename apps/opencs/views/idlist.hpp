#ifndef IDLIST_HPP
#define IDLIST_HPP

#include "ui_idlist.h"

#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

#include "../viewmodel/idlistfilter.hpp"

namespace Ui
{
class IdList;
}

class ColumnConfig
{

public:
    explicit ColumnConfig(QString key, int width) : key(key), width(width) {}
    ~ColumnConfig(){}

    QString key;
    int width;
};

class IdList : public QWidget, private Ui::IdList
{
    Q_OBJECT
    
public:
    explicit IdList(QWidget *parent = 0);
    ~IdList();
    
    void setModel(QAbstractItemModel *model);
    void setFilterModel(FilterEditModel *editModel);

    void loadColumnConfig();

private:
    FilterProxyModel *mFilterProxyModel;

    QList<ColumnConfig*> mColumnConfigs;
    void readColumnConfig(const QDomElement &element);
};

#endif
