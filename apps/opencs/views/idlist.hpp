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

class ColumnConfig
{

public:
    explicit ColumnConfig(QString key, int width) : key(key), width(width) {}
    ~ColumnConfig(){}

    QString key;
    int width;
};

class IdList : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit IdList(QWidget *parent = 0);
    ~IdList();
    
    void setModel(QAbstractItemModel *model);
    void setFilterModel(FilterEditModel *editModel);

    void loadColumnConfig();


private:
    Ui::IdList *ui;
    FilterProxyModel *mFilterProxyModel;

    QList<ColumnConfig*> mColumnConfigs;
    void readColumnConfig(const QDomElement &element);
};

#endif
