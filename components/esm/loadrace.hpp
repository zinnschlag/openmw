/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_RACE_H
#define OPENMW_ESM_RACE_H

#include <string>

#include "spelllist.hpp"

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 * Race definition
 */

struct Race
{
    struct SkillBonus
    {
        int mSkill; // SkillEnum
        int mBonus;
    };

    struct MaleFemale
    {
        int mMale, mFemale;
    };

    struct MaleFemaleF
    {
        float mMale, mFemale;
    };

    enum Flags
    {
        Playable = 0x01,
        Beast = 0x02
    };

    struct RADTstruct
    {
        // List of skills that get a bonus
        SkillBonus mBonus[7];

        // Attribute values for male/female
        MaleFemale mStrength,
                   mIntelligence,
                   mWillpower,
                   mAgility,
                   mSpeed,
                   mEndurance,
                   mPersonality,
                   mLuck;

        // The actual eye level height (in game units) is (probably) given
        // as 'height' times 128. This has not been tested yet.
        MaleFemaleF mHeight, mWeight;

        int mFlags; // 0x1 - playable, 0x2 - beast race

    }; // Size = 140 bytes

    RADTstruct mData;

    std::string mId, mName, mDescription;
    SpellList mPowers;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};

}
#endif
