#include "dataitem.hpp"

DataItem::DataItem(DataItem *parent)
    : mParentItem(parent)
    , QObject(parent)
{
}

DataItem::~DataItem()
{
    qDeleteAll(mChildItems);
}

void DataItem::appendChild(DataItem *item)
{
    mChildItems.append(item);
}

DataItem *DataItem::child(int row)
{
    return mChildItems.value(row);
}

int DataItem::childCount() const
{
    return mChildItems.count();
}

DataItem *DataItem::parent()
{
    return mParentItem;
}

int DataItem::row() const
{
    if (mParentItem)
        return mParentItem->mChildItems.indexOf(const_cast<DataItem*>(this));

    return 0;
}
