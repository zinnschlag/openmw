/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "loadligh.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Light::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mName = esm.getHNOString("FNAM");
    mIcon = esm.getHNOString("ITEX");
    assert(sizeof(mData) == 24);
    esm.getHNT(mData, "LHDT", 24);
    mScript = esm.getHNOString("SCRI");
    mSound = esm.getHNOString("SNAM");
}
void Light::save(ESMWriter &esm)
{
    esm.writeHNCString("MODL", mModel);
    esm.writeHNOCString("FNAM", mName);
    esm.writeHNOCString("ITEX", mIcon);
    esm.writeHNT("LHDT", mData, 24);
    esm.writeHNOCString("SCRI", mScript);
    esm.writeHNOCString("SNAM", mSound);
}

}
