#include "idlistfilter.hpp"

#include <QDebug>

#include "../model/filter/defaultfilter.hpp"
#include "../model/filter/matchfilter.hpp"
#include "../model/filter/unionfilter.hpp"

FilterEditModel::FilterEditModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    mRootItem = new UnionFilter("root");

    UnionFilter *defaultFilters = new UnionFilter("Default", mRootItem);
    mRootItem->appendChild(defaultFilters);

    NoFilter *noFilter = new NoFilter("NoFilter", defaultFilters);
    defaultFilters->appendChild(noFilter);

    UnionFilter *typesFiltes = new UnionFilter("Types", defaultFilters);
    defaultFilters->appendChild(typesFiltes);

    MatchFilter *actiFilter = new MatchFilter("mwType", "ACTI", typesFiltes);
    typesFiltes->appendChild(actiFilter);

    MatchFilter *alchFilter = new MatchFilter("mwType", "ALCH", typesFiltes);
    typesFiltes->appendChild(alchFilter);

    MatchFilter *scriptFilter = new MatchFilter("mwType", "SCPT", typesFiltes);
    typesFiltes->appendChild(scriptFilter);

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

    if(index.column() == 0) {
        switch(role) {
        case Qt::CheckStateRole:
            if(item->enabled())
                return Qt::Checked;
            else
                return Qt::Unchecked;
        case Qt::DisplayRole:
            return item->displayString();
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
    if(section == 0 && orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return "Name";
    else
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

    UnionFilter* unionFilter = dynamic_cast<UnionFilter*>(parentItem);
    if(unionFilter) {
        Filter *childItem = unionFilter->child(row);
        if (childItem)
            return createIndex(row, column, childItem);
    }

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

    int row = 0;

    UnionFilter* unionFilter = dynamic_cast<UnionFilter*>(parentItem);
    if(unionFilter) {
        row = unionFilter->rowOfChild(childItem);
    }

    return createIndex(row, 0, parentItem);
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

    UnionFilter* unionFilter = dynamic_cast<UnionFilter*>(parentItem);
    if(unionFilter) {
        return unionFilter->childCount();
    }

    return 0;
}

int FilterEditModel::columnCount(const QModelIndex &parent) const
{
    return 1;
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

        QSortFilterProxyModel::setSourceModel(model);
    }
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
