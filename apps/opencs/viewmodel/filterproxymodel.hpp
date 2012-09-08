#ifndef FILTERPROXYMODEL_HPP
#define FILTERPROXYMODEL_HPP

#include <QSortFilterProxyModel>

#include "filtereditmodel.hpp"

class FilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    FilterProxyModel(QObject *parent = 0);
    ~FilterProxyModel();

    void setEditModel(FilterEditModel *editModel);
    void setActiveFilter(const QModelIndex &index);

    void setSourceModel(QAbstractItemModel *model);

protected:
    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const;
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private slots:
    void headerDataChanged(Qt::Orientation,int,int);

    void filtersChanged();

private:
    FilterEditModel *mEditModel;
    QModelIndex mFilterRoot;

    QList<QString> mHeaders;
};

#endif
