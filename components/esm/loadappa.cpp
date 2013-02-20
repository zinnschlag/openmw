/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "loadappa.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{
void Apparatus::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mName = esm.getHNString("FNAM");
    esm.getHNT(mData, "AADT", 16);
    mScript = esm.getHNOString("SCRI");
    mIcon = esm.getHNString("ITEX");
}
void Apparatus::save(ESMWriter &esm)
{
    esm.writeHNCString("MODL", mModel);
    esm.writeHNCString("FNAM", mName);
    esm.writeHNT("AADT", mData, 16);
    esm.writeHNOCString("SCRI", mScript);
    esm.writeHNCString("ITEX", mIcon);
}
}
