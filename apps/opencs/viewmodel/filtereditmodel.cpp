#include "filtereditmodel.hpp"

#include <QDebug>

#include <QFile>
#include <QDir>

#include <QtXml/QDomDocument>
#include <QIcon>

#include <QMetaObject>
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
        Filter* childFilter;

        if(mChildType == "Match")
        {
            childFilter = new MatchFilter(MatchFilter::Exact, "foo", "bar", mFilter);
        }
        else if(mChildType == "SetOperation")
        {
            childFilter = new SetOperationFilter(SetOperationFilter::Union, mFilter);
            childFilter->setName("New Set Operation");
        }
        else
        {
            qDebug() << "Unknown command" << mChildType;
            return;
        }

        mModel->emitBeginInsertRows(mIndex, mFilter->childCount(), mFilter->childCount());
        mFilter->appendChild(childFilter);
        mModel->emitEndInsertRows();
    }
private:
    QString mChildType;
};

class DeleteChildCommand : public FilterCommand
{
public:
    DeleteChildCommand(FilterEditModel *model, QModelIndex index, Filter* filter)
        : FilterCommand(model, index, filter)
    {
        setText(QString("Delete child"));
    }

    virtual void undo() {
    }

    virtual void redo() {
        int row = mIndex.row();
        mModel->emitBeginRemoveRows(mIndex.parent(), row, row);

        mFilter->parent()->removeChild(row);

        mModel->emitEndRemoveRows();
    }
};





FilterEditModel::FilterEditModel(ModelItem *rootModelItem, QObject *parent)
    : QAbstractItemModel(parent)
{
    mModelRoot = rootModelItem;

    mUndoStack = new QUndoStack(this);
}

FilterEditModel::~FilterEditModel()
{
}

QVariant FilterEditModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    ModelItem *item = static_cast<ModelItem*>(index.internalPointer());

    QString roleName;
    if(role == Qt::DisplayRole)
        roleName = "display";
    else if(role == Qt::EditRole)
        roleName = "edit";
    else if(role == Qt::CheckStateRole)
        roleName = "check";
    else if(role == Qt::DecorationRole)
        roleName = "icon";
    else
        return QVariant();


    QString keySuffix = QString::number(index.column());

    QString columnKey =  roleName + "." + keySuffix;

    int infoIndex = item->metaObject()->indexOfClassInfo(columnKey.toAscii());
    if(infoIndex != -1) {
        const char* value = item->metaObject()->classInfo(infoIndex).value();

        QVariant result = item->property(value);

        //TODO
        if(role == Qt::CheckStateRole)
            return result.toBool() ? Qt::Checked : Qt::Unchecked;
        else if(role == Qt::DecorationRole)
            return QIcon(result.toString());
        else

        return result;
    } else {
        //qDebug() << "Key not found" << columnKey;
    }

    return QVariant();

//        case ItemCommandsRole:
//        {
//            QStringList actionIds;

//            //TODO
//            if (dynamic_cast<SetOperationFilter*>(filter)) {
//                actionIds.append("add");
//                actionIds.append("add");
//                actionIds.append("-");
//            }

//            actionIds.append("delete");

//            return actionIds;
//        }
//            break;
//        case ItemParamsRole:
//        {
//            QVariantList params;

//            //TODO
//            if (dynamic_cast<SetOperationFilter*>(filter)) {
//                params.append("SetOperation");
//                params.append("Match");
//                params.append("-");
//            }

//            params.append("");

//            return params;
//        }
//            break;
}

bool FilterEditModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    int column = index.column();
    Filter *filter = static_cast<Filter*>(index.internalPointer());


    QMap<QPair<int, int>, QString> commands;

    commands.insert(QPair<int, int>(0, Qt::CheckStateRole), "enabled");
    commands.insert(QPair<int, int>(0, Qt::EditRole), "name");

    commands.insert(QPair<int, int>(1, Qt::EditRole), "type");
    commands.insert(QPair<int, int>(2, Qt::EditRole), "key");
    commands.insert(QPair<int, int>(3, Qt::EditRole), "value");

    QPair<int, int> pair(column, role);
    if(commands.contains(pair)) {
        EditPropertyCommand *cmd = new EditPropertyCommand(this, index, filter, commands[pair], value);
        mUndoStack->push(cmd);

        return true;
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

    //TODO
    if(dynamic_cast<SetOperationFilter*>(filter)) {
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

void FilterEditModel::executeCommand(const QModelIndex &parent, const QString commandType, QVariant param)
{
    Filter* filter = static_cast<Filter*>(parent.internalPointer());

    QUndoCommand* cmd;

    if(commandType == "delete") {
        cmd = new DeleteChildCommand(this, parent, filter);
    } else if(commandType == "add"){
        cmd = new AddChildCommand(this, parent, filter, param.toString());
    } else {
        return;
    }

     mUndoStack->push(cmd);
}

//TODO cleanup
bool FilterEditModel::accept(const QModelIndex &index, QList<QString> headers, QList<QVariant> row)
{
    if(!index.isValid())
        return true;

    ModelItem *item = static_cast<ModelItem*>(index.internalPointer());
    FilterFile *filterFile = dynamic_cast<FilterFile*>(item);

    return dynamic_cast<Filter*>(filterFile->child(0))->accept(headers, row);
}

QModelIndex FilterEditModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    ModelItem *parentItem;

    // The root object is represented as an invalid index
    if (!parent.isValid())
        parentItem = mModelRoot;
    else
        parentItem = static_cast<ModelItem*>(parent.internalPointer());

    ModelItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);

    return QModelIndex();
}

QModelIndex FilterEditModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    ModelItem *childItem = static_cast<ModelItem*>(index.internalPointer());
    ModelItem *parentItem = childItem->parent();

    if (parentItem == mModelRoot)
        return QModelIndex();

    int row = parentItem ? parentItem->childRow(childItem) : 0;

    return createIndex(row, 0, parentItem);
}

int FilterEditModel::rowCount(const QModelIndex &parent) const
{
//    if (parent.column() > 0)
//        return 0;

    // The root object is represented as an invalid index
    ModelItem *parentItem;
    if (!parent.isValid())
        parentItem = mModelRoot;
    else
        parentItem = static_cast<ModelItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int FilterEditModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QUndoStack *FilterEditModel::undoStack() const
{
    return mUndoStack;
}


