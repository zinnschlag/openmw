/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "loadarmo.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void PartReferenceList::load(ESMReader &esm)
{
    while (esm.isNextSub("INDX"))
    {
        PartReference pr;
        esm.getHT(pr.mPart); // The INDX byte
        pr.mMale = esm.getHNOString("BNAM");
        pr.mFemale = esm.getHNOString("CNAM");
        mParts.push_back(pr);
    }
}

void PartReferenceList::save(ESMWriter &esm)
{
    for (std::vector<PartReference>::iterator it = mParts.begin(); it != mParts.end(); ++it)
    {
        esm.writeHNT("INDX", it->mPart);
        esm.writeHNOString("BNAM", it->mMale);
        esm.writeHNOString("CNAM", it->mFemale);
    }
}

void Armor::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mName = esm.getHNString("FNAM");
    mScript = esm.getHNOString("SCRI");
    esm.getHNT(mData, "AODT", 24);
    mIcon = esm.getHNOString("ITEX");
    mParts.load(esm);
    mEnchant = esm.getHNOString("ENAM");
}

void Armor::save(ESMWriter &esm)
{
    esm.writeHNCString("MODL", mModel);
    esm.writeHNCString("FNAM", mName);
    esm.writeHNOCString("SCRI", mScript);
    esm.writeHNT("AODT", mData, 24);
    esm.writeHNOCString("ITEX", mIcon);
    mParts.save(esm);
    esm.writeHNOCString("ENAM", mEnchant);
}

}
