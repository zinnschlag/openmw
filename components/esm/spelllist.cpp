/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "spelllist.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM {

void SpellList::load(ESMReader &esm)
{
    while (esm.isNextSub("NPCS")) {
        mList.push_back(esm.getHString());
    }
}

void SpellList::save(ESMWriter &esm)
{
    for (std::vector<std::string>::iterator it = mList.begin(); it != mList.end(); ++it) {
        esm.writeHNString("NPCS", *it, 32);
    }
}

}
