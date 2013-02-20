/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "mandatoryid.hpp"

#include "../world/idcollection.hpp"

CSMTools::MandatoryIdStage::MandatoryIdStage (const CSMWorld::IdCollectionBase& idCollection,
    const CSMWorld::UniversalId& collectionId, const std::vector<std::string>& ids)
: mIdCollection (idCollection), mCollectionId (collectionId), mIds (ids)
{}

int CSMTools::MandatoryIdStage::setup()
{
    return mIds.size();
}

void CSMTools::MandatoryIdStage::perform (int stage, std::vector<std::string>& messages)
{
    if (mIdCollection.searchId (mIds.at (stage))==-1 ||
        mIdCollection.getRecord (mIds.at (stage)).isDeleted())
        messages.push_back (mCollectionId.toString() + "|Missing mandatory record: " + mIds.at (stage));
}