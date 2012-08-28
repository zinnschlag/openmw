#include "filtereditmodel.hpp"

#include <QDebug>
#include <QFile>
#include <QtXml/QDomDocument>
#include <QIcon>

#include "../model/filter/defaultfilter.hpp"
#include "../model/filter/matchfilter.hpp"
#include "../model/filter/unionfilter.hpp"

class EditPropertyCommand : public QUndoCommand
{
public:
    EditPropertyCommand(Filter *filter, QString propertyName, QVariant newValue)
        : mFilter(filter)
        , mPropertyName(propertyName)
        , mNewValue(newValue)
    {
        mOldValue = filter->property(propertyName.toAscii());

        setText(QString("Set %2 to %3 for %1").arg(mFilter->name()).arg(mPropertyName).arg(mNewValue.toString()));
    }

    virtual void undo() {
        mFilter->setProperty(mPropertyName.toAscii(), mOldValue);
    }

    virtual void redo() {
        mFilter->setProperty(mPropertyName.toAscii(), mNewValue);
    }
private:
    Filter *mFilter;
    QString mPropertyName;

    QVariant mOldValue;
    QVariant mNewValue;
};

FilterEditModel::FilterEditModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    mRootItem = new SetOperationFilter(SetOperationFilter::Union);
    mRootItem->setName("root");

    mUndoStack = new QUndoStack(this);
}

FilterEditModel::~FilterEditModel()
{
    delete mRootItem;
}

void FilterEditModel::load()
{
    SetOperationFilter *newRoot = new SetOperationFilter(SetOperationFilter::Union);
    newRoot->setName("root");

    QFile file(":/filters.xml");
    if (file.open(QIODevice::ReadOnly))
    {
        QDomDocument document("FilterTree");

        QString parseError;
        int parseErrorRow;
        int parseErrorColumn;

        if (document.setContent(&file, &parseError, &parseErrorRow, &parseErrorColumn))
            readFilter(document.firstChildElement(), newRoot);
        else
            qDebug() << "Parse error" << parseError << parseErrorRow << parseErrorColumn;

        file.close();
    }
    else
        qDebug() << "Opening file failed";


    mRootItem = newRoot;

    emit dataChanged(QModelIndex(), QModelIndex());
}

void FilterEditModel::readFilter(const QDomElement &element, Filter *parent)
{

    Filter *childFilter = 0;

    QString name = element.tagName();
    if (name == "SetOperation")
    {
        QString type = element.attribute("type", "Union");
        SetOperationFilter::OperationType matchType;
        if(type == "Union")
        {
            matchType = SetOperationFilter::Union;
        }
        else if(type == "Intersection")
        {
            matchType = SetOperationFilter::Intersection;
        }
        else
        {
            qWarning() << "Unknown type" << type;
        }

        childFilter = new SetOperationFilter(matchType, parent);
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
        qWarning() << "Unknown filter type" << element.tagName();
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
        case ItemCommandsRole:
        {
            QStringList actionIds;

            if (dynamic_cast<FilterList*>(filter)) {
                actionIds.append("addSetOperation");
                actionIds.append("addMatch");
                actionIds.append("-");
            }

            actionIds.append("delete");

            return actionIds;
        }
            break;
        case Qt:: DecorationRole:
            SetOperationFilter *setOpFilter = dynamic_cast<SetOperationFilter*>(filter);
            if(setOpFilter) {
                switch(setOpFilter->type()) {
                case SetOperationFilter::Union:
                    return QIcon(":/icon/filter/union.png");
                case SetOperationFilter::Intersection:
                    return QIcon(":/icon/filter/intersection.png");
                }
            }

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
            bool newValue = value == Qt::Checked ? true : false;
            EditPropertyCommand *cmd = new EditPropertyCommand(item, "enabled", newValue);
            mUndoStack->push(cmd);

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
                MatchFilter::MatchType matchType = (MatchFilter::MatchType)value.toInt();

                EditPropertyCommand *cmd = new EditPropertyCommand(matchFilter, "type", matchType);
                mUndoStack->push(cmd);
                goto ok;
            }
            if(column == 2) {
                EditPropertyCommand *cmd = new EditPropertyCommand(matchFilter, "key", value);
                mUndoStack->push(cmd);
                goto ok;
            }
            if(column == 3) {
                EditPropertyCommand *cmd = new EditPropertyCommand(matchFilter, "value", value);
                mUndoStack->push(cmd);
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

void FilterEditModel::executeCommand(const QString name, const QModelIndex &parent)
{
    if(name == "delete") {
         removeRow(parent.row(), parent.parent());
         return;
    }

    Filter* filter = static_cast<Filter*>(parent.internalPointer());
    FilterList* filterList = dynamic_cast<FilterList*>(filter);

    Filter* childFilter;

    if(name == "addMatch")
    {
        childFilter = new MatchFilter(MatchFilter::Exact, "foo", "bar", filterList);
    }
    else if(name == "addSetOperation")
    {
        childFilter = new SetOperationFilter(SetOperationFilter::Union, filterList);
        childFilter->setName("New Set Operation");
    }
    else
    {
        qDebug() << "Unknown command" << name;
        return;
    }

    beginInsertRows(parent, filterList->childCount(), filterList->childCount());
    filterList->appendChild(childFilter);
    endInsertRows();
}

bool FilterEditModel::accept(QList<QString> headers, QList<QVariant> row)
{
    return mRootItem->accept(headers, row);
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


