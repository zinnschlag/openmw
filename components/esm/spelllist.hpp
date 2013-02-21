/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_SPELLLIST_H
#define OPENMW_ESM_SPELLLIST_H

#include <vector>
#include <string>

namespace ESM
{
    class ESMReader;
    class ESMWriter;

    /** A list of references to spells and spell effects. This is shared
     between the records BSGN, NPC and RACE.
     */
    struct SpellList
    {
        std::vector<std::string> mList;

        void load(ESMReader &esm);
        void save(ESMWriter &esm);
    };
}

#endif

