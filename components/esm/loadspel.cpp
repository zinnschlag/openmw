/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "loadspel.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Spell::load(ESMReader &esm)
{
    mName = esm.getHNOString("FNAM");
    esm.getHNT(mData, "SPDT", 12);
    mEffects.load(esm);
}

void Spell::save(ESMWriter &esm)
{
    esm.writeHNOCString("FNAM", mName);
    esm.writeHNT("SPDT", mData, 12);
    mEffects.save(esm);
}

}
