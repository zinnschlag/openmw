/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "record.hpp"

CSMWorld::RecordBase::~RecordBase() {}

bool CSMWorld::RecordBase::isDeleted() const
{
    return mState==State_Deleted || mState==State_Erased;
}


bool CSMWorld::RecordBase::isErased() const
{
    return mState==State_Erased;
}


bool CSMWorld::RecordBase::isModified() const
{
    return mState==State_Modified || mState==State_ModifiedOnly;
}