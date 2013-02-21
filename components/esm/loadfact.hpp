/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_FACT_H
#define OPENMW_ESM_FACT_H

#include <string>
#include <vector>

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 * Faction definitions
 */

// Requirements for each rank
struct RankData
{
    int mAttribute1, mAttribute2; // Attribute level

    int mSkill1, mSkill2; // Skill level (faction skills given in
    // skillID below.) You need one skill at
    // level 'skill1' and two skills at level
    // 'skill2' to advance to this rank.

    int mFactReaction; // Reaction from faction members
};

struct Faction
{
    std::string mId, mName;

    struct FADTstruct
    {
        // Which attributes we like
        int mAttribute1, mAttribute2;

        RankData mRankData[10];

        int mSkillID[6]; // IDs of skills this faction require
        int mUnknown; // Always -1?
        int mIsHidden; // 1 - hidden from player
    }; // 240 bytes

    FADTstruct mData;

    struct Reaction
    {
        std::string mFaction;
        int mReaction;
    };

    std::vector<Reaction> mReactions;

    // Name of faction ranks (may be empty for NPC factions)
    std::string mRanks[10];

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};
}
#endif
