/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "loadrace.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Race::load(ESMReader &esm)
{
    mName = esm.getHNString("FNAM");
    esm.getHNT(mData, "RADT", 140);
    mPowers.load(esm);
    mDescription = esm.getHNOString("DESC");
}
void Race::save(ESMWriter &esm)
{
    esm.writeHNCString("FNAM", mName);
    esm.writeHNT("RADT", mData, 140);
    mPowers.save(esm);
    esm.writeHNOString("DESC", mDescription);
}

}
