#include "filterproxymodel.hpp"

FilterProxyModel::FilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
    , mEditModel(0)
{
}

FilterProxyModel::~FilterProxyModel()
{
}

void FilterProxyModel::setEditModel(FilterEditModel *editModel)
{
    mEditModel = editModel;
    connect(mEditModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(filtersChanged()));
}

void FilterProxyModel::setSourceModel(QAbstractItemModel *model)
{
    QAbstractItemModel* currentModel = this->sourceModel();
    if (currentModel)
    {
        disconnect(currentModel, SIGNAL(headerDataChanged(Qt::Orientation,int,int)), this, SLOT(headerDataChanged(Qt::Orientation,int,int)));
    }

    if (model)
    {
        connect(model, SIGNAL(headerDataChanged(Qt::Orientation,int,int)), this, SLOT(headerDataChanged(Qt::Orientation,int,int)));

        QSortFilterProxyModel::setSourceModel(model);
    }
}

bool FilterProxyModel::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const
{
    return true;
}

bool FilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (!mEditModel)
        return true;

    QList<QVariant> row;

    for (int i = 0; i < mHeaders.size(); i++)
    {
        QModelIndex index = sourceModel()->index(sourceRow, i, sourceParent);
        QVariant columnValue = sourceModel()->data(index);

        row.append(columnValue);
    }

    return mEditModel->accept(mHeaders, row);
}

void FilterProxyModel::headerDataChanged(Qt::Orientation, int, int)
{
    mHeaders.clear();

    int columns = sourceModel()->columnCount();
    for (int i = 0; i < columns; i++)
    {
        QString columnName = sourceModel()->headerData(i, Qt::Horizontal).toString();
        mHeaders.insert(i, columnName);
    }
}

void FilterProxyModel::filtersChanged()
{
    invalidateFilter();
}
