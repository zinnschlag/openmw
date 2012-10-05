#include "datamodel.hpp"

#include <QDebug>

#include <QFile>
#include <QDir>

#include <QtXml/QDomDocument>
#include <QIcon>

#include <QMetaObject>
#include <QMetaProperty>

#include "../model/gui/componentitem.hpp"

#include "../model/filter/defaultfilter.hpp"
#include "../model/filter/matchfilter.hpp"
#include "../model/filter/setoperationfilter.hpp"

#include "../persistence/esmserializer.hpp"

#include <QProcessEnvironment>

class FilterCommand : public QUndoCommand
{
public:
    FilterCommand(DataModel *model, QModelIndex index, Filter *filter)
        :QUndoCommand()
        , mModel(model)
        , mIndex(index)
        , mFilter(filter)
    {}

protected:
    DataModel *mModel;
    QPersistentModelIndex mIndex;
    Filter *mFilter;
};

class EditPropertyCommand : public FilterCommand
{
public:
    EditPropertyCommand(DataModel *model, QModelIndex index, Filter *filter, QString propertyName, QVariant newValue)
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
    AddChildCommand(DataModel *model, QModelIndex index, Filter *filter, QString childType)
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
    DeleteChildCommand(DataModel *model, QModelIndex index, Filter* filter)
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





DataModel::DataModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    mModelRoot = new ModelItem();

    filterParentItem = new ModelItem("filter", mModelRoot);
    mModelRoot->appendChild(filterParentItem);

    esmFilesParent = new ModelItem("esm", mModelRoot);
    mModelRoot->appendChild(esmFilesParent);

    guiRootItem = new ModelItem("gui", mModelRoot);
    mModelRoot->appendChild(guiRootItem);


    mUndoStack = new QUndoStack(this);
}

DataModel::~DataModel()
{
    mModelRoot->deleteLater();
}


void DataModel::loadGuiData()
{
    guiRootItem->appendChild(new WidgetItem("IdList", "ID List", Qt::RightDockWidgetArea, guiRootItem));
    guiRootItem->appendChild(new WidgetItem("FilterTree", "Filter Tree", Qt::LeftDockWidgetArea, guiRootItem));
    guiRootItem->appendChild(new WidgetItem("FilterEditor", "Filter Editor", Qt::LeftDockWidgetArea, guiRootItem));

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    if(env.contains("OPENCS_DEBUG_GUI"))
    {
        guiRootItem->appendChild(new WidgetItem("UndoRedo", "Undo / Redo", Qt::LeftDockWidgetArea, guiRootItem));
        guiRootItem->appendChild(new WidgetItem("ItemModel", "Data Model", Qt::BottomDockWidgetArea, guiRootItem));
    }
}

void DataModel::loadFilterDirectory(QString path)
{
    FilterDom *filterDom = new FilterDom(this);
    QDir filterDirectory(":/filter/");
    foreach(QString filterFileName, filterDirectory.entryList())
    {
        QString filterFilePath = filterDirectory.absoluteFilePath(filterFileName);

        filterParentItem->appendChild(filterDom->loadFile(filterFilePath, filterParentItem));
    }
}



void DataModel::loadEsmFile(QString filePath)
{
    EsmFile *esmFile = new EsmFile(filePath, esmFilesParent);

    EsmSerializer *serializer = new EsmSerializer(this);
    serializer->load(esmFile);

    //FIXME hardcoded model index
    emitBeginInsertRows(index(1, 0), rowCount(), rowCount() + 1);
    esmFilesParent->appendChild(esmFile);
    emitEndInsertRows();
}


//FIXME global
QModelIndex lastContextIndex;

void DataModel::fillContextMenu(QMenu *menu, const QModelIndex &index)
{

    lastContextIndex = index;

    ModelItem *item = static_cast<ModelItem*>(index.internalPointer());

    if (dynamic_cast<SetOperationFilter*>(item)) {

        //FIXME copy-paste
        QAction *openAct = new QAction("Add SetOperation", menu);
        openAct->setProperty("cmd", "addSetOp");
        connect(openAct, SIGNAL(triggered()), this, SLOT(actionExecuted()));
        menu->addAction(openAct);

        //FIXME copy-paste
        QAction *addMatch = new QAction("Add Match", menu);
        addMatch->setProperty("cmd", "addMatch");
        connect(addMatch, SIGNAL(triggered()), this, SLOT(actionExecuted()));
        menu->addAction(addMatch);

    }

    if(dynamic_cast<Filter*>(item)) {
        QAction *spacer = new QAction(menu);
        spacer->setSeparator(true);
        menu->addAction(spacer);

        //FIXME copy-paste
        QAction *addMatch = new QAction("Delete", menu);
        addMatch->setProperty("cmd", "delete");
        connect(addMatch, SIGNAL(triggered()), this, SLOT(actionExecuted()));
        menu->addAction(addMatch);
    }
}


void DataModel::actionExecuted()
{
    QAction *action = qobject_cast<QAction*>(QObject::sender());
    if(action) {

        QModelIndex index = lastContextIndex;

        ModelItem *item = static_cast<ModelItem*>(index.internalPointer());
        Filter *filterItem = dynamic_cast<Filter*>(item);

        QString command = action->property("cmd").toString();


        QUndoCommand* cmd;

        if(command == "addSetOp") {
            cmd = new AddChildCommand(this, index, filterItem, "SetOperation");
        } else if(command == "addMatch"){
            cmd = new AddChildCommand(this, index, filterItem, "Match");
        } else if(command == "delete"){
            cmd = new DeleteChildCommand(this, index, filterItem);
        } else {
            qDebug() << "Unknown command";
            return;
        }

        mUndoStack->push(cmd);

    } else {
        qDebug() << "Action executed slot not called by QAction";
    }
}

//TODO cleanup
bool DataModel::accept(const QModelIndex &index, QList<QString> headers, QList<QVariant> row)
{
    if(!index.isValid())
        return true;

    ModelItem *item = static_cast<ModelItem*>(index.internalPointer());
    FilterFile *filterFile = dynamic_cast<FilterFile*>(item);

    return dynamic_cast<Filter*>(filterFile->child(0))->accept(headers, row);
}


QUndoStack *DataModel::undoStack() const
{
    return mUndoStack;
}

// QAbstractTableModel
// =============================================================================

QVariant DataModel::data(const QModelIndex &index, int role) const
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
}

bool DataModel::setData(const QModelIndex &index, const QVariant &value, int role)
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

Qt::ItemFlags DataModel::flags(const QModelIndex &index) const
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


QModelIndex DataModel::index(int row, int column, const QModelIndex &parent) const
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

QModelIndex DataModel::parent(const QModelIndex &index) const
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

int DataModel::rowCount(const QModelIndex &parent) const
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

int DataModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

