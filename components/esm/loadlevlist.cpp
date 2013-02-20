/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "loadlevlist.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void LeveledListBase::load(ESMReader &esm)
{
    esm.getHNT(mFlags, "DATA");
    esm.getHNT(mChanceNone, "NNAM");

    if (esm.isNextSub("INDX"))
    {
        int len;
        esm.getHT(len);
        mList.resize(len);
    }
    else
        return;

    // TODO: Merge with an existing lists here. This can be done
    // simply by adding the lists together, making sure that they are
    // sorted by level. A better way might be to exclude repeated
    // items. Also, some times we don't want to merge lists, just
    // overwrite. Figure out a way to give the user this option.

    for (size_t i = 0; i < mList.size(); i++)
    {
        LevelItem &li = mList[i];
        li.mId = esm.getHNString(mRecName);
        esm.getHNT(li.mLevel, "INTV");
    }
}
void LeveledListBase::save(ESMWriter &esm)
{
    esm.writeHNT("DATA", mFlags);
    esm.writeHNT("NNAM", mChanceNone);
    esm.writeHNT<int>("INDX", mList.size());
    
    for (std::vector<LevelItem>::iterator it = mList.begin(); it != mList.end(); ++it)
    {
        esm.writeHNCString(mRecName, it->mId);
        esm.writeHNT("INTV", it->mLevel);
    }
}

}
