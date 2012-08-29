#include "filtereditmodel.hpp"

#include <QDebug>
#include <QFile>
#include <QtXml/QDomDocument>
#include <QIcon>
#include <QMetaProperty>

#include "../model/filter/defaultfilter.hpp"
#include "../model/filter/matchfilter.hpp"
#include "../model/filter/setoperationfilter.hpp"

class FilterCommand : public QUndoCommand
{
public:
    FilterCommand(FilterEditModel *model, QModelIndex index, Filter *filter)
        :QUndoCommand()
        , mModel(model)
        , mIndex(index)
        , mFilter(filter)
    {}

protected:
    FilterEditModel *mModel;
    QPersistentModelIndex mIndex;
    Filter *mFilter;
};

class EditPropertyCommand : public FilterCommand
{
public:
    EditPropertyCommand(FilterEditModel *model, QModelIndex index, Filter *filter, QString propertyName, QVariant newValue)
        : FilterCommand(model, index, filter)
        , mPropertyName(propertyName)
        , mNewValue(newValue)
    {
        mOldValue = filter->property(propertyName.toAscii());

        setText(QString("Set %2 to %3 for %1").arg(mFilter->name()).arg(mPropertyName).arg(mNewValue.toString()));
    }

    virtual void undo() {
        mFilter->setProperty(mPropertyName.toAscii(), mOldValue);
        mModel->emitDataChanged(mIndex);
    }

    virtual void redo() {
        mFilter->setProperty(mPropertyName.toAscii(), mNewValue);
        mModel->emitDataChanged(mIndex);
    }
private:
    QString mPropertyName;

    QVariant mOldValue;
    QVariant mNewValue;
};



class AddChildCommand : public FilterCommand
{
public:
    AddChildCommand(FilterEditModel *model, QModelIndex index, Filter *filter, QString childType)
        : FilterCommand(model, index, filter)
        , mChildType(childType)
    {
        setText(QString("Add child %1").arg(childType));
    }

    virtual void undo() {
    }

    virtual void redo() {
        FilterList* filterList = dynamic_cast<FilterList*>(mFilter);

        Filter* childFilter;

        if(mChildType == "addMatch")
        {
            childFilter = new MatchFilter(MatchFilter::Exact, "foo", "bar", filterList);
        }
        else if(mChildType == "addSetOperation")
        {
            childFilter = new SetOperationFilter(SetOperationFilter::Union, filterList);
            childFilter->setName("New Set Operation");
        }
        else
        {
            qDebug() << "Unknown command" << mChildType;
            return;
        }

        mModel->emitBeginInsertRows(mIndex, filterList->childCount(), filterList->childCount());
        filterList->appendChild(childFilter);
        mModel->emitEndInsertRowsd();
    }
private:
    QString mChildType;
};




class LoadXmlCommand : public FilterCommand
{
public:
    LoadXmlCommand(FilterEditModel *model, QModelIndex index, Filter *filter, QString filePath)
        : FilterCommand(model, index, filter)
        , mFile(filePath)
    {
        setText(QString("Load XML %1").arg(filePath));
    }

    virtual void undo() {
    }

    virtual void redo() {
        load();
    }

    void load()
    {
        if (mFile.open(QIODevice::ReadOnly))
        {
            QDomDocument document("FilterTree");

            QString parseError;
            int parseErrorRow;
            int parseErrorColumn;

            if (document.setContent(&mFile, &parseError, &parseErrorRow, &parseErrorColumn))
                readFilter(document.firstChildElement(), mFilter);
            else
                qDebug() << "Parse error" << parseError << parseErrorRow << parseErrorColumn;

            mFile.close();
        }
        else
            qDebug() << "Opening file failed";

        mModel->emitDataChanged(QModelIndex());
    }

    void readFilter(const QDomElement &element, Filter *parent)
    {

        Filter *childFilter = 0;

        QString name = element.tagName();
        if (name == "SetOperation")
        {
            QString type = element.attribute("type", "Union");
            SetOperationFilter::OperationType matchType = SetOperationFilter::Union;
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
            QString matchTypeName = element.attribute("type", "Exact");

            MatchFilter::MatchType matchType = MatchFilter::Exact;
            if(matchTypeName == "Exact")
            {
                matchType = MatchFilter::Exact;
            }
            else if(matchTypeName == "Wildcard")
            {
                matchType = MatchFilter::Wildcard;
            }
            else if(matchTypeName == "Regex")
            {
                matchType = MatchFilter::Regex;
            }
            else
            {
                qWarning() << "Unknown match type" << matchTypeName;
            }

            QDomElement keyElement = element.firstChildElement("Key");
            QDomElement matchElement = element.firstChildElement("Value");

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


        QString childName;

        FilterList* childFilterList = dynamic_cast<FilterList*>(childFilter);
        if(childFilterList)
        {
            QDomNode childNode = element.firstChild();
            while (!childNode.isNull())
            {
                if (childNode.isElement())
                {
                    QDomElement childElement = childNode.toElement();

                    if(childElement.tagName() == "Name")
                        childName = childElement.text();
                    else
                        readFilter(childElement, childFilter);
                }
                childNode = childNode.nextSibling();
            }
        }

        childFilter->setName(childName);

        FilterList* parentFilter = dynamic_cast<FilterList*>(parent);
        if (parentFilter)
            parentFilter->appendChild(childFilter);
        else
            qWarning() << "Parent is not a collection";
    }

private:
    QFile mFile;
};





FilterEditModel::FilterEditModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    mRootItem = new SetOperationFilter(SetOperationFilter::Union);
    mRootItem->setName("root");

    mUndoStack = new QUndoStack(this);

    LoadXmlCommand *cmd = new LoadXmlCommand(this, QModelIndex(), mRootItem, ":/filters.xml");
    mUndoStack->push(cmd);
}

FilterEditModel::~FilterEditModel()
{
    delete mRootItem;
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
        {
            return filter->name();
        }
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

        SetOperationFilter *setOpFilter = dynamic_cast<SetOperationFilter*>(filter);
        if(setOpFilter) {
            if(index.column() == 1)
                return setOpFilter->type();
        }
    }


    return QVariant();
}

bool FilterEditModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    int column = index.column();
    Filter *filter = static_cast<Filter*>(index.internalPointer());

    if(column == 0) {
        if (role == Qt::CheckStateRole) {
            bool newValue = value == Qt::Checked ? true : false;
            EditPropertyCommand *cmd = new EditPropertyCommand(this, index, filter, "enabled", newValue);
            mUndoStack->push(cmd);

            return true;
        }
        else if (role == Qt::EditRole) {
            EditPropertyCommand *cmd = new EditPropertyCommand(this, index, filter, "name", value.toString());
            mUndoStack->push(cmd);
            return true;
        }
    }

    if (role == Qt::EditRole)
    {
        MatchFilter* matchFilter = dynamic_cast<MatchFilter*>(filter);
        if(matchFilter) {
            if(column == 1) {
                MatchFilter::MatchType matchType = (MatchFilter::MatchType)value.toInt();

                EditPropertyCommand *cmd = new EditPropertyCommand(this, index, matchFilter, "type", matchType);
                mUndoStack->push(cmd);
                return true;
            }
            if(column == 2) {
                EditPropertyCommand *cmd = new EditPropertyCommand(this, index, matchFilter, "key", value);
                mUndoStack->push(cmd);
                return true;
            }
            if(column == 3) {
                EditPropertyCommand *cmd = new EditPropertyCommand(this, index, matchFilter, "value", value);
                mUndoStack->push(cmd);
                return true;
            }
        }

        SetOperationFilter *setOpFilter = dynamic_cast<SetOperationFilter*>(filter);
        if(setOpFilter) {
            if(column == 1) {
                SetOperationFilter::OperationType matchType = (SetOperationFilter::OperationType)value.toInt();

                EditPropertyCommand *cmd = new EditPropertyCommand(this, index, setOpFilter, "type", matchType);
                mUndoStack->push(cmd);
                return true;
            }
        }
    }

    return false;
}

Qt::ItemFlags FilterEditModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags = Qt::ItemIsSelectable;

    if (index.column() == 0)
        flags |= Qt::ItemIsUserCheckable;

    Filter* filter = static_cast<Filter*>(index.internalPointer());

    if(dynamic_cast<FilterList*>(filter)) {
        if(index.column() < 2) {
            flags |= Qt::ItemIsEnabled;
        }
    } else if (dynamic_cast<DefaultFilter*>(filter)){
        if(index.column() == 0) {
            flags |= Qt::ItemIsEnabled;
        }
    } else {
        flags |= Qt::ItemIsEnabled;
    }

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

    AddChildCommand *cmd = new AddChildCommand(this, parent, filter, name);
    mUndoStack->push(cmd);
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


