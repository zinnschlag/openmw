
#include "ptr.hpp"

#include <cassert>

#include "containerstore.hpp"
#include "class.hpp"


/* This shouldn't really be here. */
MWWorld::LiveCellRefBase::LiveCellRefBase(std::string type, const ESM::CellRef &cref)
  : mClass(&Class::get(type)), mRef(cref), mData(mRef)
{
}


const std::string& MWWorld::Ptr::getTypeName() const
{
    if(mRef != 0)
        return mRef->mClass->getTypeName();
    throw std::runtime_error("Can't get type name from an empty object.");
}

ESM::CellRef& MWWorld::Ptr::getCellRef() const
{
    assert(mRef);

    if (mContainerStore)
        mContainerStore->flagAsModified();

    return mRef->mRef;
}

MWWorld::RefData& MWWorld::Ptr::getRefData() const
{
    assert(mRef);

    if (mContainerStore)
        mContainerStore->flagAsModified();

    return mRef->mData;
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
