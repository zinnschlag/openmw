#include "openfileproxymodel.hpp"

OpenFileProxyModel::OpenFileProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
}

bool OpenFileProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    //show only selected files witch all masters selected
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    if (sourceModel()->data(index, Qt::CheckStateRole) == Qt::Checked &&
        sourceModel()->flags(index) & Qt::ItemIsEnabled)
        return true;
    return false;
}

QVariant OpenFileProxyModel::data(const QModelIndex &index, int role) const
{
    //filter checkboxes
    if (role == Qt::CheckStateRole)
        return QVariant();
    return QSortFilterProxyModel::data(index, role);
}