/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "loadench.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Enchantment::load(ESMReader &esm)
{
    esm.getHNT(mData, "ENDT", 16);
    mEffects.load(esm);
}

void Enchantment::save(ESMWriter &esm)
{
    esm.writeHNT("ENDT", mData, 16);
    mEffects.save(esm);
}

}
