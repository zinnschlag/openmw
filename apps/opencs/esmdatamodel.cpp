#include <QtGui>

#include <string>
#include <iostream>

#include <components/esm/esm_reader.hpp>
#include <components/esm/records.hpp>

#include "esmdataitem.hpp"
#include "esmdatamodel.hpp"

#include "model/activator.hpp"
#include "model/potion.hpp"

#include "QMetaObject"

ESMDataModel::ESMDataModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    mRootItem = new DataItem();
}

ESMDataModel::~ESMDataModel()
{
    delete mRootItem;
}

void ESMDataModel::loadEsmFile(QString file)
{
    qDebug() << "Trying to open esm:" << file;
    beginResetModel();

    EsmFile *esmFile = new EsmFile(file, mRootItem);
    mRootItem->appendChild(esmFile);

    std::string stdStrFileName = file.toStdString();

    ESM::ESMReader esm;
    esm.setEncoding("default");
    esm.open(stdStrFileName);

    while(esm.hasMoreRecs()) {
        esm.getContext();

        ESM::NAME recordName = esm.getRecName();
        esm.getRecHeader();

        std::string id = esm.getHNOString("NAME");
        QString recordId = QString::fromStdString(id);

        ESMDataItem defaultLoadable;
        ESMDataItem *child = NULL;

        switch(recordName.val) {
        case ESM::REC_ACTI:
            child = new ActivatorDataItem(esmFile);
            break;
        case ESM::REC_ALCH:
            child = new PotionDataItem(esmFile);
            break;
        default:
            child = &defaultLoadable;
            break;
        }

        if(child) {
            if(child != &defaultLoadable) {
                child->setId(recordId);
                esmFile->appendChild(child);
            }

            child->load(esm);
        }
    }

    updateHeaders(mRootItem);


    endResetModel();
}

QVariant ESMDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    DataItem *item = static_cast<DataItem*>(index.internalPointer());

    const QMetaObject* metaObject = item->metaObject();

    int column = index.column();
    QVariant columnName = m_ColumnNames.at(column);

    int propertyIndexOfOfName = metaObject->indexOfProperty(columnName.toString().toAscii());
    if(propertyIndexOfOfName != -1) {
        return metaObject->property(propertyIndexOfOfName).read(item);
    } else {
        return QVariant();
    }
}

Qt::ItemFlags ESMDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QVariant ESMDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if(section < 0 || section >= m_ColumnNames.size()) {
            qWarning() << "Header section out of range" << section;
            return QVariant();
        }

        return QVariant(m_ColumnNames.at(section));
    } else {
        //qWarning() << "unknown orientation or role" << orientation << role;
        return QVariant();
    }
}

QModelIndex ESMDataModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    DataItem *parentItem;

    // The root object is represented as an invalid index
    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<DataItem*>(parent.internalPointer());

    DataItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex ESMDataModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    DataItem *childItem = static_cast<DataItem*>(index.internalPointer());
    DataItem *parentItem = childItem->parent();

    if (parentItem == mRootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int ESMDataModel::rowCount(const QModelIndex &parent) const
{
    DataItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<ESMDataItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int ESMDataModel::columnCount(const QModelIndex &parent) const
{
   return m_ColumnNames.size();
}

void ESMDataModel::updateHeaders(DataItem *parent)
{
    for(int i=0;i<parent->childCount();i++) {
        DataItem *child = parent->child(i);

        const QMetaObject* metaObject = child->metaObject();

        for(int i = 1; i < metaObject->propertyCount(); ++i) {
            QMetaProperty metaProperty = metaObject->property(i);

            QVariant header = metaProperty.name();

            if(!m_ColumnNames.contains(header)) {
                m_ColumnNames.append(header);
                qDebug() <<"added header" << header;
            }
        }

        updateHeaders(child);


//        for(int u = 0; u<child->columnCount(); u++) {
//            QVariant header = child->headerData(u);

//            if(!m_ColumnNames.contains(header)) {
//                m_ColumnNames.append(header);
//                qDebug() <<"added header" << header;
//            }
//        }
    }
}
