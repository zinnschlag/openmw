#include <QStringList>

#include "esmdataitem.hpp"

ESMDataItem::ESMDataItem(const QList<QVariant> &data, ESMDataItem *parent)
{
    mParentItem = parent;
    mItemData = data;
}

ESMDataItem::~ESMDataItem()
{
    qDeleteAll(mChildItems);
}

void ESMDataItem::appendChild(ESMDataItem *item)
{
    mChildItems.append(item);
}

ESMDataItem *ESMDataItem::child(int row)
{
    return mChildItems.value(row);
}

int ESMDataItem::childCount() const
{
    return mChildItems.count();
}

int ESMDataItem::columnCount() const
{
    return mItemData.count();
}

QVariant ESMDataItem::data(int column) const
{
    return mItemData.value(column);
}

ESMDataItem *ESMDataItem::parent()
{
    return mParentItem;
}

int ESMDataItem::row() const
{
    if (mParentItem)
        return mParentItem->mChildItems.indexOf(const_cast<ESMDataItem*>(this));

    return 0;
}
