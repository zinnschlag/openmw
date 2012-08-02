#include "idlistfilter.hpp"

#include <QDebug>

FilterEditModel::FilterEditModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    mRootItem = new Filter();


    UnionFilter *defaultFilters = new UnionFilter("Default", mRootItem);
    mRootItem->appendChild(defaultFilters);

    MatchFilter *actiFilter = new MatchFilter("mwType", "ACTI", defaultFilters);
    defaultFilters->appendChild(actiFilter);

    MatchFilter *alchFilter = new MatchFilter("mwType", "ALCH", defaultFilters);
    defaultFilters->appendChild(alchFilter);

    UnionFilter *customFilters = new UnionFilter("Custom", mRootItem);
    mRootItem->appendChild(customFilters);
}

FilterEditModel::~FilterEditModel()
{
    delete mRootItem;
}

QVariant FilterEditModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Filter *item = static_cast<Filter*>(index.internalPointer());

    if(role == Qt::CheckStateRole && index.column() == 0) {
        if(item->enabled())
            return Qt::Checked;
        else
            return Qt::Unchecked;
    }

    if (role == Qt::DisplayRole) {
        switch(index.column()) {
        case 0:
            return item->displayName();
        case 1:
            return item->displayType();
        }
    }

    return QVariant();
}

bool FilterEditModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    Filter *item = static_cast<Filter*>(index.internalPointer());

    if(role == Qt::CheckStateRole && index.column() == 0) {
        if(value == Qt::Checked)
            item->setEnabled(true);
        else
            item->setEnabled(false);

        emit dataChanged(index, index);
        return true;
    }

    return false;
}

Qt::ItemFlags FilterEditModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    if (index.column() == 0)
        flags |= Qt::ItemIsUserCheckable;

    return flags;
}

bool FilterEditModel::accept(QString key, QString value)
{
    return mRootItem->accept(key, value);
}

QVariant FilterEditModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(section) {
    case 0:
        return "Name";
    case 1:
        return "Type";
    }
    return QVariant();
}

QModelIndex FilterEditModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    Filter *parentItem;

    // The root object is represented as an invalid index
    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<Filter*>(parent.internalPointer());

    Filter *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex FilterEditModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    Filter *childItem = static_cast<Filter*>(index.internalPointer());
    Filter *parentItem = childItem->parent();

    if (parentItem == mRootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int FilterEditModel::rowCount(const QModelIndex &parent) const
{
    Filter *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<Filter*>(parent.internalPointer());

    return parentItem->childCount();
}

int FilterEditModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}



FilterProxyModel::FilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    mEditModel = new FilterEditModel(this);
    connect(mEditModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(invalidate()));
}

bool FilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    return true;

    int columns = sourceModel()->columnCount(sourceParent);

    for(int i=0; i< columns; i++) {
        QString columnName = sourceModel()->headerData(i, Qt::Horizontal).toString();

        QModelIndex index = sourceModel()->index(sourceRow, i, sourceParent);
        QString columnValue = sourceModel()->data(index).toString();


        if(mEditModel->accept(columnName, columnValue))
            return true;
    }

    return false;
}
