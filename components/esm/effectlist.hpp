/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_EFFECTLIST_H
#define OPENMW_ESM_EFFECTLIST_H

#include <vector>

namespace ESM
{
    class ESMReader;
    class ESMWriter;

    #pragma pack(push)
    #pragma pack(1)

    /** Defines a spell effect. Shared between SPEL (Spells), ALCH
     (Potions) and ENCH (Item enchantments) records
     */
    struct ENAMstruct
    {
        // Magical effect, hard-coded ID
        short mEffectID;

        // Which skills/attributes are affected (for restore/drain spells
        // etc.)
        signed char mSkill, mAttribute; // -1 if N/A

        // Other spell parameters
        int mRange; // 0 - self, 1 - touch, 2 - target (RangeType enum)
        int mArea, mDuration, mMagnMin, mMagnMax;
    };
    #pragma pack(pop)

    struct EffectList
    {

        std::vector<ENAMstruct> mList;

        void load(ESMReader &esm);
        void save(ESMWriter &esm);
    };
    
}

#endif
