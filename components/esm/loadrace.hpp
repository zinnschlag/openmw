#ifndef _ESM_RACE_H
#define _ESM_RACE_H

#include <string>

#include "record.hpp"
#include "spelllist.hpp"

namespace ESM
{
/*
 * Race definition
 */

struct Race : public Record
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

    std::string mName, mDescription;
    SpellList mPowers;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);

    int getName() { return REC_RACE; }
};

}
#endif
