#include <QtGui>
#include <QMetaObject>

#include <string>
#include <iostream>

#include "esmdatamodel.hpp"

#include <components/esm/esm_reader.hpp>
#include <components/esm/records.hpp>

#include "../model/esm/esmfile.hpp"
#include "../model/esm/esmdataitem.hpp"

#include "../model/esm/record/activator.hpp"
#include "../model/esm/record/potion.hpp"
#include "../model/esm/record/script.hpp"
#include "../model/esm/record/setting.hpp"

ESMDataModel::ESMDataModel(QObject *parent)
    : QAbstractTableModel(parent)
    , mRowCount(0)
{
}

ESMDataModel::~ESMDataModel()
{
}

void ESMDataModel::setRootItem(ModelItem *rootItem)
{
    beginResetModel();

    mRootItem = rootItem;

    mRowCount = mRootItem->childCount();
    for (int i = 0; i < mRowCount; i++)
    {
        ModelItem *child = mRootItem->child(i);
        const QMetaObject *childMeta = child->metaObject();

        for (int u = 0; u < childMeta->propertyCount(); u++)
        {
            const QMetaProperty prop = child->metaObject()->property(u);

            QHash<const QMetaObject*, int>* map;

            if (!mNamedProperties.contains(prop.name()))
            {
                map = new QHash<const QMetaObject*, int>();
                mNamedProperties.insert(prop.name(), map);
            }
            else
            {
                map = mNamedProperties.value(prop.name());
            }

            map->insert(childMeta, u);
        }
    }

    mColumnIds = mNamedProperties.keys();

    emit headerDataChanged(Qt::Horizontal, 0, mNamedProperties.size() - 1);
    endResetModel();

}

int ESMDataModel::rowCount(const QModelIndex &parent) const
{
    return mRowCount;
}

int ESMDataModel::columnCount(const QModelIndex &parent) const
{
   return mColumnIds.size();
}

QVariant ESMDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    ModelItem *baseItem = mRootItem;

    int column = index.column();


    if(role == Qt::DisplayRole)
    {
        ModelItem *rowItem = baseItem->child(index.row());

        return valueAtColumn(rowItem, column);
    }
    else if(role == Qt::TextAlignmentRole)
    {
        ModelItem *rowItem = baseItem->child(index.row());

        bool ok;
        valueAtColumn(rowItem, column).toDouble(&ok);
        if(ok) {
            return QVariant(Qt::AlignRight);
        }
    }
    else if (role == PossibleValuesRole)
    {
        QVariantList possibleValues;

        for (int i = 0; i<baseItem->childCount(); i++)
        {
            ModelItem *rowItem = baseItem->child(i);

            QVariant fieldData = valueAtColumn(rowItem, column);
            if (!fieldData.isValid())
                continue;

            if (!possibleValues.contains(fieldData))
                possibleValues.append(fieldData);
        }

        return possibleValues;
    }

    return QVariant();
}

QVariant ESMDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal &&
        role == Qt::DisplayRole &&
        section >= 0 &&
        section < mNamedProperties.size())
    {
        return QVariant(mColumnIds.at(section));
    }

    return QVariant();
}

Qt::ItemFlags ESMDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QVariant ESMDataModel::valueAtColumn(const ModelItem *rowItem, int column) const
{
    QString columnId = mColumnIds.at(column);
    QHash<const QMetaObject*, int> *map = mNamedProperties.value(columnId);
    if (map->contains(rowItem->metaObject()))
    {
        int propertyNo = map->value(rowItem->metaObject());

        return rowItem->metaObject()->property(propertyNo).read(rowItem);
    }
    return QVariant();
}
