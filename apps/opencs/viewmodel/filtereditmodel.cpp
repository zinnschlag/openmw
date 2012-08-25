#include "filtereditmodel.hpp"

#include <QDebug>
#include <QFile>
#include <QtXml/QDomDocument>
#include <QIcon>

#include "../model/filter/defaultfilter.hpp"
#include "../model/filter/matchfilter.hpp"
#include "../model/filter/unionfilter.hpp"
#include "../model/filter/intersectionfilter.hpp"

FilterEditModel::FilterEditModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    mRootItem = new UnionFilter();
    mRootItem->setName("root");

    mUndoStack = new QUndoStack(this);
}

FilterEditModel::~FilterEditModel()
{
    delete mRootItem;
}

void FilterEditModel::load()
{
    UnionFilter *newRoot = new UnionFilter();
    newRoot->setName("root");

    QFile file(":/filters.xml");
    if (file.open(QIODevice::ReadOnly))
    {
        QDomDocument document("FilterTree");

        QString parseError;

        if (document.setContent(&file, &parseError))
            readFilter(document.firstChildElement(), newRoot);
        else
            qDebug() << "Parse error" << parseError;

        file.close();
    }
    else
        qDebug() << "Opening file failed";


    mRootItem = newRoot;

    emit dataChanged(QModelIndex(), QModelIndex());
}

void FilterEditModel::readFilter(const QDomElement &element, Filter *parent)
{

    Filter *childFilter;

    QString name = element.tagName();
    if (name == "Union")
    {
        childFilter = new UnionFilter(parent);
    }
    else if (name == "Intersection")
    {
        childFilter = new IntersectionFilter(parent);
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
        return;
    }

    QString enabled = element.attribute("active", "true");
    childFilter->setEnabled(enabled == "true" ? true : false);


    QDomElement childName = element.firstChildElement("Name");
    childFilter->setName(childName.text());


    FilterList* childFilterList = dynamic_cast<FilterList*>(childFilter);
    if(childFilterList) {
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

    FilterList* parentFilter = dynamic_cast<FilterList*>(parent);
    if (parentFilter)
        parentFilter->appendChild(childFilter);
    else
        qWarning() << "Parent is not a collection";
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
        case Qt::DisplayRole:
            return filter->name();
        case Qt::CheckStateRole:
            return filter->enabled() ? Qt::Checked : Qt::Unchecked;
        case ChildActionsRole:
        {
            QStringList actionIds;

            if (dynamic_cast<FilterList*>(filter)) {
                actionIds.append("addUnion");
                actionIds.append("addIntersection");
                actionIds.append("addMatch");
                actionIds.append("-");
            }

            actionIds.append("delete");

            return actionIds;
        }
            break;
        case Qt:: DecorationRole:
            if (dynamic_cast<UnionFilter*>(filter))
                return QIcon(":/icon/filter/union.png");
            if (dynamic_cast<IntersectionFilter*>(filter))
                return QIcon(":/icon/filter/intersection.png");

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

    if(role == Qt::EditRole || role == Qt::DisplayRole) {

        if(index.column() == 0)
            return filter->name();

        MatchFilter *matchFilter = dynamic_cast<MatchFilter*>(filter);
        if(matchFilter) {

            if(index.column() == 1)
                return matchFilter->type();
            if(index.column() == 2)
                return matchFilter->key();
            if(index.column() == 3)
                return matchFilter->value();
        }
    }


    return QVariant();
}

bool FilterEditModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    bool success = true;

    int column = index.column();
    Filter *item = static_cast<Filter*>(index.internalPointer());

    if(column == 0) {
        if (role == Qt::CheckStateRole) {
            item->setEnabled(value == Qt::Checked ? true : false);
            goto ok;
        }
        else if (role == Qt::EditRole) {
            item->setName(value.toString());
            goto ok;
        }
    }


    if (role == Qt::EditRole)
    {
        MatchFilter* matchFilter = dynamic_cast<MatchFilter*>(item);
        if(matchFilter) {
            if(column == 1) {
                matchFilter->setType((MatchFilter::MatchType)value.toInt());
                goto ok;
            }
            if(column == 2) {
                matchFilter->setKey(value.toString());
                goto ok;
            }
            if(column == 3) {
                matchFilter->setValue(value.toString());
                goto ok;
            }
        }
    }

    success = false;
    ok:
    if(success)
        emit dataChanged(index, index);

    return success;
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

    FilterList* unionFilter = dynamic_cast<FilterList*>(filter);
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

void FilterEditModel::runAction(const QString name, const QModelIndex &parent)
{
    Filter* filter = static_cast<Filter*>(parent.internalPointer());


    if(name == "delete") {
         removeRow(parent.row(), parent.parent());
    }

    if(name == "addUnion" || name == "addIntersection" || name == "addMatch") {



        UnionFilter* unionFilter = dynamic_cast<UnionFilter*>(filter);
        if (unionFilter)
        {
            Filter *childFilter;
            if(name == "addUnion") {
                childFilter = new UnionFilter(unionFilter);
                childFilter->setName("New Union");
            }
            else if(name == "addIntersection") {
                childFilter = new IntersectionFilter(unionFilter);
                childFilter->setName("New Intersection");
            }
            else if(name == "addMatch") {
                childFilter = new MatchFilter(MatchFilter::Exact, "foo", "bar", unionFilter);
            }
            else
                return;


            beginInsertRows(parent, unionFilter->childCount(), unionFilter->childCount());
            unionFilter->appendChild(childFilter);
            endInsertRows();
        }

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

    FilterList* unionFilter = dynamic_cast<FilterList*>(parentItem);
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


    FilterList* filterList = dynamic_cast<FilterList*>(parentItem);

    int row = filterList ? filterList->rowOfChild(childItem) : 0;

    return createIndex(row, 0, parentItem);
}

int FilterEditModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    Filter *parentItem = parent.isValid() ? static_cast<Filter*>(parent.internalPointer()) : mRootItem;

    FilterList* filterList = dynamic_cast<FilterList*>(parentItem);

    return filterList ? filterList->childCount() : 0;
}

int FilterEditModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}





QUndoStack *FilterEditModel::undoStack() const
{
    return mUndoStack;
}
