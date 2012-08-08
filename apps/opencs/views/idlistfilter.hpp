#ifndef IDLISTFILTER_HPP
#define IDLISTFILTER_HPP

#include <QMap>

#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

#include "../model/filter/filter.hpp"

namespace Ui {
class IdList;
}

class FilterEditModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    FilterEditModel(QObject *parent);
    ~FilterEditModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool accept(QList<QString> headers, QList<QVariant> row);

private:
    Filter *mRootItem;
};

class FilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    FilterProxyModel(QObject *parent = 0);

    FilterEditModel *editModel() { return mEditModel;}

    void setSourceModel(QAbstractItemModel *model);

protected:
    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const;
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private slots:
    void headerDataChanged(Qt::Orientation,int,int);

private:
    FilterEditModel *mEditModel;

    QList<QString> mHeaders;
};

#endif
