/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "loadalch.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{
void Potion::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mIcon = esm.getHNOString("TEXT"); // not ITEX here for some reason
    mScript = esm.getHNOString("SCRI");
    mName = esm.getHNOString("FNAM");
    esm.getHNT(mData, "ALDT", 12);
    mEffects.load(esm);
}
void Potion::save(ESMWriter &esm)
{
    esm.writeHNCString("MODL", mModel);
    esm.writeHNOCString("TEXT", mIcon);
    esm.writeHNOCString("SCRI", mScript);
    esm.writeHNOCString("FNAM", mName);
    esm.writeHNT("ALDT", mData, 12);
    mEffects.save(esm);
}
}
