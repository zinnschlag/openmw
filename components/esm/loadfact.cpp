/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "loadfact.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Faction::load(ESMReader &esm)
{
    mName = esm.getHNString("FNAM");

    // Read rank names. These are optional.
    int i = 0;
    while (esm.isNextSub("RNAM") && i < 10)
        mRanks[i++] = esm.getHString();

    // Main data struct
    esm.getHNT(mData, "FADT", 240);

    if (mData.mIsHidden > 1)
        esm.fail("Unknown flag!");

    // Read faction response values
    while (esm.hasMoreSubs())
    {
        Reaction r;
        r.mFaction = esm.getHNString("ANAM");
        esm.getHNT(r.mReaction, "INTV");
        mReactions.push_back(r);
    }
}
void Faction::save(ESMWriter &esm)
{
    esm.writeHNCString("FNAM", mName);
    
    for (int i = 0; i < 10; i++)
    {
        if (mRanks[i].empty())
            break;

        esm.writeHNString("RNAM", mRanks[i], 32);
    }

    esm.writeHNT("FADT", mData, 240);
    
    for (std::vector<Reaction>::iterator it = mReactions.begin(); it != mReactions.end(); ++it)
    {
        esm.writeHNString("ANAM", it->mFaction);
        esm.writeHNT("INTV", it->mReaction);
    }
}

}
