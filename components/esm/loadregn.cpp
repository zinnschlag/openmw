/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "loadregn.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Region::load(ESMReader &esm)
{
    mName = esm.getHNString("FNAM");

    if (esm.getVer() == VER_12)
        esm.getHNExact(&mData, sizeof(mData) - 2, "WEAT");
    else if (esm.getVer() == VER_13)
        esm.getHNExact(&mData, sizeof(mData), "WEAT");
    else
        esm.fail("Don't know what to do in this version");

    mSleepList = esm.getHNOString("BNAM");

    esm.getHNT(mMapColor, "CNAM");

    while (esm.hasMoreSubs())
    {
        SoundRef sr;
        esm.getHNT(sr, "SNAM", 33);
        mSoundList.push_back(sr);
    }
}
void Region::save(ESMWriter &esm)
{
    esm.writeHNCString("FNAM", mName);
    
    if (esm.getVersion() == VER_12)
        esm.writeHNT("WEAT", mData, sizeof(mData) - 2);
    else
        esm.writeHNT("WEAT", mData);
    
    esm.writeHNOCString("BNAM", mSleepList);
    
    esm.writeHNT("CNAM", mMapColor);
    for (std::vector<SoundRef>::iterator it = mSoundList.begin(); it != mSoundList.end(); ++it)
    {
        esm.writeHNT<SoundRef>("SNAM", *it);
    }
}

}
