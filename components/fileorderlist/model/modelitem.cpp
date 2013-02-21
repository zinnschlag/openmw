/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

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
        return 1;
        //return mParentItem->childRow(const_cast<ModelItem*>(this));
        //return mParentItem->mChildItems.indexOf(const_cast<ModelItem*>(this));

    return -1;
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
