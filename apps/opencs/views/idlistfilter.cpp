#include "idlistfilter.hpp"

#include <QDebug>
#include <QFile>
#include <QtXml/QDomDocument>
#include <QIcon>

#include "../model/filter/defaultfilter.hpp"
#include "../model/filter/matchfilter.hpp"
#include "../model/filter/unionfilter.hpp"

FilterEditModel::FilterEditModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    mRootItem = new UnionFilter("root");
}

FilterEditModel::~FilterEditModel()
{
    delete mRootItem;
}

void FilterEditModel::load()
{
    UnionFilter *newRoot = new UnionFilter("root");

    QFile file(":/filters.xml");
    if (file.open(QIODevice::ReadOnly))
    {
        QDomDocument document("FilterTree");

        QString parseError;

        if (document.setContent(&file, &parseError))
        {
            readFilter(document.firstChildElement(), newRoot);
        }
        else
        {
            qDebug() << "Parse error" << parseError;
        }

        file.close();
    }
    else
    {
        qDebug() << "Opening file failed";
    }


    mRootItem = newRoot;

    emit dataChanged(QModelIndex(), QModelIndex());
}

void FilterEditModel::readFilter(const QDomElement &element, Filter *parent)
{

    Filter *childFilter;

    QString name = element.tagName();
    if (name == "Union")
    {
        childFilter = new UnionFilter("", parent);

        QDomNode childNode = element.firstChild();
        while (!childNode.isNull())
        {
            if (childNode.isElement())
            {
                QDomElement childElement = childNode.toElement();
                readFilter(childElement, childFilter);
            }
            childNode = childNode.nextSibling();
        }
    }
    else if (name == "Match")
    {
        QDomElement keyElement = element.firstChildElement("Key");
        QDomElement matchElement = element.firstChildElement("Value");

        QString matchTypeName = element.attribute("type", "Exact");
        MatchFilter::MatchType matchType = MatchFilter::Exact;
        if(matchTypeName == "Exact") {
            matchType = MatchFilter::Exact;
        } else if(matchTypeName == "Wildcard") {
            matchType = MatchFilter::Wildcard;
        } else if(matchTypeName == "Regex") {
            matchType = MatchFilter::Regex;
        } else {
            qWarning() << "Unknown match type" << matchTypeName;
        }

        childFilter = new MatchFilter(matchType, keyElement.text(), matchElement.text(), parent);
    }
    else if (name == "Default")
    {
        childFilter = new DefaultFilter(parent);
    }
    else
    {
        qWarning() << "Invalid tagName" << element.tagName();
    }

    QString enabled = element.attribute("active", "true");
    childFilter->setEnabled(enabled == "true" ? true : false);

    UnionFilter* parentUnion = qobject_cast<UnionFilter*>(parent);
    if (parentUnion)
    {
        parentUnion->appendChild(childFilter);
    }
    else
    {
        qWarning() << "Parent is not a collection";
    }
}




QVariant FilterEditModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Filter *filter = static_cast<Filter*>(index.internalPointer());

    if (index.column() == 0)
    {
        switch(role)
        {
        case Qt::CheckStateRole:
            if(filter->enabled())
                return Qt::Checked;
            else
                return Qt::Unchecked;
        case Qt::DisplayRole:
            return filter->displayString();
        case Qt:: DecorationRole:
            if (dynamic_cast<UnionFilter*>(filter))
                return QIcon(":/icon/filter/union.png");

            MatchFilter *matchFilter = dynamic_cast<MatchFilter*>(filter);
            if(matchFilter) {
                switch(matchFilter->type()) {
                case MatchFilter::Exact:
                    return QIcon(":/icon/filter/exact.png");
                case MatchFilter::Wildcard:
                    return QIcon(":/icon/filter/wildcard.png");
                case MatchFilter::Regex:
                    return QIcon(":/icon/filter/regex.png");
                }
            }
            break;
        }
    }

    return QVariant();
}

bool FilterEditModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    Filter *item = static_cast<Filter*>(index.internalPointer());

    if (role == Qt::CheckStateRole && index.column() == 0)
    {
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

bool FilterEditModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Filter* filter = static_cast<Filter*>(parent.internalPointer());

    UnionFilter* unionFilter = dynamic_cast<UnionFilter*>(filter);
    if (unionFilter)
    {
        beginRemoveRows(parent, row, row + count);

        unionFilter->removeChild(row);

        endRemoveRows();
        return true;
    } else {
        qWarning() << "Cannot remove child from non collection filter";
        return false;
    }
}

//FIXME Copy Paste
void FilterEditModel::addUnionFilter(const QModelIndex &parent)
{
    Filter* filter = static_cast<Filter*>(parent.internalPointer());

    UnionFilter* unionFilter = dynamic_cast<UnionFilter*>(filter);
    if (unionFilter)
    {
        beginInsertRows(parent, unionFilter->childCount(), unionFilter->childCount());

        UnionFilter *childFilter = new UnionFilter("New Union", unionFilter);
        unionFilter->appendChild(childFilter);

        endInsertRows();
    }
}

//FIXME Copy Paste
void FilterEditModel::addMatchFilter(const QModelIndex &parent)
{
    Filter* filter = static_cast<Filter*>(parent.internalPointer());

    UnionFilter* unionFilter = dynamic_cast<UnionFilter*>(filter);
    if (unionFilter)
    {
        beginInsertRows(parent, unionFilter->childCount(), unionFilter->childCount());

        MatchFilter *childFilter = new MatchFilter(MatchFilter::Exact, "foo", "bar", unionFilter);
        unionFilter->appendChild(childFilter);

        endInsertRows();
    }
}

bool FilterEditModel::accept(QList<QString> headers, QList<QVariant> row)
{
    return mRootItem->accept(headers, row);
}

QVariant FilterEditModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section == 0 && orientation == Qt::Horizontal && role == Qt::DisplayRole)
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
    if (unionFilter)
    {
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
    if (unionFilter)
    {
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
    if (unionFilter)
    {
        return unionFilter->childCount();
    }

    return 0;
}

int FilterEditModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

//=======================================================================================

FilterProxyModel::FilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
    , mEditModel(0)
{
}

void FilterProxyModel::setEditModel(FilterEditModel *editModel)
{
    mEditModel = editModel;
    connect(mEditModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(invalidate()));
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
