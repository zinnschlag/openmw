#include "modelitem.hpp"

ModelItem::ModelItem(ModelItem *parent)
    : mParentItem(parent)
    , QObject(parent)
{
}

ModelItem::~ModelItem()
{
    qDeleteAll(mChildItems);
}


ModelItem *ModelItem::parent()
{
    return mParentItem;
}

int ModelItem::row() const
{
    if (mParentItem)
        return mParentItem->mChildItems.indexOf(const_cast<ModelItem*>(this));

    return 0;
}


int ModelItem::childCount() const
{
    return mChildItems.count();
}

int ModelItem::childRow(ModelItem *child) const
{
    Q_ASSERT(child);

    return mChildItems.indexOf(child);
}

ModelItem *ModelItem::child(int row)
{
    return mChildItems.value(row);
}


void ModelItem::appendChild(ModelItem *item)
{
    mChildItems.append(item);
}

void ModelItem::removeChild(int row)
{
    mChildItems.removeAt(row);
}
