#include "loadrace.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Race::load(ESMReader &esm)
{
    mName = esm.getHNString("FNAM");

    esm.getHNT(mData, "RADT", 140);
    for (size_t i = 0; i < 7; i++)
    {
        mData.mBonus[i].mSkill = le32toh(mData.mBonus[i].mSkill);
        mData.mBonus[i].mBonus = le32toh(mData.mBonus[i].mBonus);
    }
    mData.mStrength.mMale = le32toh(mData.mStrength.mMale);
    mData.mStrength.mFemale = le32toh(mData.mStrength.mFemale);
    mData.mIntelligence.mMale = le32toh(mData.mIntelligence.mMale);
    mData.mIntelligence.mFemale = le32toh(mData.mIntelligence.mFemale);
    mData.mWillpower.mMale = le32toh(mData.mWillpower.mMale);
    mData.mWillpower.mFemale = le32toh(mData.mWillpower.mFemale);
    mData.mAgility.mMale = le32toh(mData.mAgility.mMale);
    mData.mAgility.mFemale = le32toh(mData.mAgility.mFemale);
    mData.mSpeed.mMale = le32toh(mData.mSpeed.mMale);
    mData.mSpeed.mFemale = le32toh(mData.mSpeed.mFemale);
    mData.mEndurance.mMale = le32toh(mData.mEndurance.mMale);
    mData.mEndurance.mFemale = le32toh(mData.mEndurance.mFemale);
    mData.mPersonality.mMale = le32toh(mData.mPersonality.mMale);
    mData.mPersonality.mFemale = le32toh(mData.mPersonality.mFemale);
    mData.mLuck.mMale = le32toh(mData.mLuck.mMale);
    mData.mLuck.mFemale = le32toh(mData.mLuck.mFemale);
    mData.mHeight.mMale = letoh_float(mData.mHeight.mMale);
    mData.mHeight.mFemale = letoh_float(mData.mHeight.mFemale);
    mData.mWeight.mMale = letoh_float(mData.mWeight.mMale);
    mData.mWeight.mFemale = letoh_float(mData.mWeight.mFemale);
    mData.mFlags = le32toh(mData.mFlags);

    mPowers.load(esm);
    mDescription = esm.getHNOString("DESC");
}
void Race::save(ESMWriter &esm)
{
    esm.writeHNCString("FNAM", mName);

    for (size_t i = 0; i < 7; i++)
    {
        mData.mBonus[i].mSkill = htole32(mData.mBonus[i].mSkill);
        mData.mBonus[i].mBonus = htole32(mData.mBonus[i].mBonus);
    }
    mData.mStrength.mMale = htole32(mData.mStrength.mMale);
    mData.mStrength.mFemale = htole32(mData.mStrength.mFemale);
    mData.mIntelligence.mMale = htole32(mData.mIntelligence.mMale);
    mData.mIntelligence.mFemale = htole32(mData.mIntelligence.mFemale);
    mData.mWillpower.mMale = htole32(mData.mWillpower.mMale);
    mData.mWillpower.mFemale = htole32(mData.mWillpower.mFemale);
    mData.mAgility.mMale = htole32(mData.mAgility.mMale);
    mData.mAgility.mFemale = htole32(mData.mAgility.mFemale);
    mData.mSpeed.mMale = htole32(mData.mSpeed.mMale);
    mData.mSpeed.mFemale = htole32(mData.mSpeed.mFemale);
    mData.mEndurance.mMale = htole32(mData.mEndurance.mMale);
    mData.mEndurance.mFemale = htole32(mData.mEndurance.mFemale);
    mData.mPersonality.mMale = htole32(mData.mPersonality.mMale);
    mData.mPersonality.mFemale = htole32(mData.mPersonality.mFemale);
    mData.mLuck.mMale = htole32(mData.mLuck.mMale);
    mData.mLuck.mFemale = htole32(mData.mLuck.mFemale);
    mData.mHeight.mMale = htole_float(mData.mHeight.mMale);
    mData.mHeight.mFemale = htole_float(mData.mHeight.mFemale);
    mData.mWeight.mMale = htole_float(mData.mWeight.mMale);
    mData.mWeight.mFemale = htole_float(mData.mWeight.mFemale);
    mData.mFlags = htole32(mData.mFlags);
    esm.writeHNT("RADT", mData, 140);

    mPowers.save(esm);
    esm.writeHNOString("DESC", mDescription);
}

}
