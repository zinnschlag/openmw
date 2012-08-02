#include "idlistfilter.hpp"

#include <QDebug>

FilterEditModel::FilterEditModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    mRootItem = new Filter();


    UnionFilter *defaultFilters = new UnionFilter("Default", mRootItem);
    mRootItem->appendChild(defaultFilters);

    NoFilter *noFilter = new NoFilter("NoFilter", defaultFilters);
    defaultFilters->appendChild(noFilter);

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

bool FilterEditModel::accept(QList<QString> headers, QList<QVariant> row)
{
    return mRootItem->accept(headers, row);
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



FilterProxyModel::FilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    mEditModel = new FilterEditModel(this);
    connect(mEditModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(invalidate()));
}

void FilterProxyModel::setSourceModel(QAbstractItemModel *model)
{
    QAbstractItemModel* currentModel = this->sourceModel();
    if (currentModel) {
        disconnect(currentModel, SIGNAL(headerDataChanged(Qt::Orientation,int,int)), this, SLOT(headerDataChanged(Qt::Orientation,int,int)));
    }

    if (model) {
        connect(model, SIGNAL(headerDataChanged(Qt::Orientation,int,int)), this, SLOT(headerDataChanged(Qt::Orientation,int,int)));
    }

    QSortFilterProxyModel::setSourceModel(model);
}

bool FilterProxyModel::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const
{
    return true;
}

bool FilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QList<QVariant> row;

    for(int i=0; i<mHeaders.size(); i++) {
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
    for(int i=0; i< columns; i++) {
        QString columnName = sourceModel()->headerData(i, Qt::Horizontal).toString();
        mHeaders.insert(i, columnName);
    }
}
