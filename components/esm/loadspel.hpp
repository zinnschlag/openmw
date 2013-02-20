/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_SPEL_H
#define OPENMW_ESM_SPEL_H

#include <string>

#include "effectlist.hpp"

namespace ESM
{

class ESMReader;
class ESMWriter;

struct Spell
{
    enum SpellType
    {
        ST_Spell = 0,   // Normal spell, must be cast and costs mana
        ST_Ability = 1, // Inert ability, always in effect
        ST_Blight = 2,  // Blight disease
        ST_Disease = 3, // Common disease
        ST_Curse = 4,   // Curse (?)
        ST_Power = 5    // Power, can use once a day
    };

    enum Flags
    {
        F_Autocalc = 1,
        F_PCStart = 2,
        F_Always = 4 // Casting always succeeds
    };

    struct SPDTstruct
    {
        int mType; // SpellType
        int mCost; // Mana cost
        int mFlags; // Flags
    };

    SPDTstruct mData;
    std::string mId, mName;
    EffectList mEffects;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};
}
#endif
