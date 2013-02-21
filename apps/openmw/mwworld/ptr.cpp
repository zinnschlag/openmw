/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "ptr.hpp"

#include <cassert>

#include "containerstore.hpp"

ESM::CellRef& MWWorld::Ptr::getCellRef() const
{
    assert (mCellRef);

    if (mContainerStore)
        mContainerStore->flagAsModified();

    return *mCellRef;
}

MWWorld::RefData& MWWorld::Ptr::getRefData() const
{
    assert (mRefData);

    if (mContainerStore)
        mContainerStore->flagAsModified();

    return *mRefData;
}

void MWWorld::Ptr::setContainerStore (ContainerStore *store)
{
    assert (store);
    assert (!mCell);

    mContainerStore = store;
}

MWWorld::ContainerStore *MWWorld::Ptr::getContainerStore() const
{
    return mContainerStore;
}
