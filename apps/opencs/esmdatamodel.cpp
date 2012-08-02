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
    : QAbstractTableModel(parent)
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

    ESM::ESMReader reader;
    reader.setEncoding("default");
    reader.open(stdStrFileName);

    while(reader.hasMoreRecs()) {
        reader.getContext();

        ESM::NAME recordType = reader.getRecName();
        reader.getRecHeader();

        std::string id = reader.getHNOString("NAME");
        QString recordId = QString::fromStdString(id);

        ESMDataItem *child = NULL;

        switch(recordType.val) {
        case ESM::REC_ACTI:
            child = new ActivatorDataItem(esmFile);
            break;
        case ESM::REC_ALCH:
            child = new PotionDataItem(esmFile);
            break;
        default:
            child = new ESMDataItem(esmFile);
            break;
        }

        child->setRecordType(QString::fromStdString(recordType.toString()));

        child->setId(recordId);
        esmFile->appendChild(child);

        child->load(reader);
    }

    updateHeaders(mRootItem);


    int totalRow = 0;
    for(int i=0; i<mRootItem->childCount(); i++) {
        DataItem *firstLevelChild = mRootItem->child(i);
        for(int u=0; u<firstLevelChild->childCount(); u++) {
            totalRow ++;
        }
    }

    mRowCount = totalRow;

    endResetModel();
}

int ESMDataModel::rowCount(const QModelIndex &parent) const
{
    return mRowCount;
}

int ESMDataModel::columnCount(const QModelIndex &parent) const
{
   return m_ColumnNames.size();
}

QVariant ESMDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    DataItem *baseItem = mRootItem->child(0);

    DataItem *rowItem = baseItem->child(index.row());

    const QMetaObject* metaObject = rowItem->metaObject();

    int column = index.column();
    QVariant columnName = m_ColumnNames.at(column);

    int propertyIndexOfOfName = metaObject->indexOfProperty(columnName.toString().toAscii());
    if(propertyIndexOfOfName != -1) {
        return metaObject->property(propertyIndexOfOfName).read(rowItem);
    } else {
        return QVariant();
    }
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

Qt::ItemFlags ESMDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
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
    }

    emit headerDataChanged(Qt::Horizontal, 0, m_ColumnNames.size() -1 );
}
