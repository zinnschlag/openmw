/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "loadweap.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Weapon::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mName = esm.getHNOString("FNAM");
    esm.getHNT(mData, "WPDT", 32);
    mScript = esm.getHNOString("SCRI");
    mIcon = esm.getHNOString("ITEX");
    mEnchant = esm.getHNOString("ENAM");
}
void Weapon::save(ESMWriter &esm)
{
    esm.writeHNCString("MODL", mModel);
    esm.writeHNOCString("FNAM", mName);
    esm.writeHNT("WPDT", mData, 32);
    esm.writeHNOCString("SCRI", mScript);
    esm.writeHNOCString("ITEX", mIcon);
    esm.writeHNOCString("ENAM", mEnchant);
}

}
