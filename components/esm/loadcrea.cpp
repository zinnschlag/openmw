#include "loadcrea.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM {

void Creature::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mOriginal = esm.getHNOString("CNAM");
    mName = esm.getHNOString("FNAM");
    mScript = esm.getHNOString("SCRI");

    esm.getHNT(mData, "NPDT", 96);
    mData.mType = le32toh(mData.mType);
    mData.mLevel = le32toh(mData.mLevel);
    mData.mStrength = le32toh(mData.mStrength);
    mData.mIntelligence = le32toh(mData.mIntelligence);
    mData.mWillpower = le32toh(mData.mWillpower);
    mData.mAgility = le32toh(mData.mAgility);
    mData.mSpeed = le32toh(mData.mSpeed);
    mData.mEndurance = le32toh(mData.mEndurance);
    mData.mPersonality = le32toh(mData.mPersonality);
    mData.mLuck = le32toh(mData.mLuck);
    mData.mHealth = le32toh(mData.mHealth);
    mData.mMana = le32toh(mData.mMana);
    mData.mFatigue = le32toh(mData.mFatigue);
    mData.mSoul = le32toh(mData.mSoul);
    mData.mCombat = le32toh(mData.mCombat);
    mData.mMagic = le32toh(mData.mMagic);
    mData.mStealth = le32toh(mData.mStealth);
    for (size_t i = 0; i < 6; i++)
        mData.mAttack[i] = le32toh(mData.mAttack[i]);
    mData.mGold = le32toh(mData.mGold);

    esm.getHNT(mFlags, "FLAG");
    mFlags = le32toh(mFlags);

    mScale = 1.0;
    esm.getHNOT(mScale, "XSCL");
    mScale = letoh_float(mScale);

    mInventory.load(esm);
    mSpells.load(esm);

    if (esm.isNextSub("AIDT"))
    {
        esm.getHExact(&mAiData, sizeof(mAiData));
        mHasAI = true;
    }
    else
        mHasAI = false;

    mAiPackage.load(esm);
    esm.skipRecord();
}

void Creature::save(ESMWriter &esm)
{
    esm.writeHNCString("MODL", mModel);
    esm.writeHNOCString("CNAM", mOriginal);
    esm.writeHNOCString("FNAM", mName);
    esm.writeHNOCString("SCRI", mScript);

    mData.mType = htole32(mData.mType);
    mData.mLevel = htole32(mData.mLevel);
    mData.mStrength = htole32(mData.mStrength);
    mData.mIntelligence = htole32(mData.mIntelligence);
    mData.mWillpower = htole32(mData.mWillpower);
    mData.mAgility = htole32(mData.mAgility);
    mData.mSpeed = htole32(mData.mSpeed);
    mData.mEndurance = htole32(mData.mEndurance);
    mData.mPersonality = htole32(mData.mPersonality);
    mData.mLuck = htole32(mData.mLuck);
    mData.mHealth = htole32(mData.mHealth);
    mData.mMana = htole32(mData.mMana);
    mData.mFatigue = htole32(mData.mFatigue);
    mData.mSoul = htole32(mData.mSoul);
    mData.mCombat = htole32(mData.mCombat);
    mData.mMagic = htole32(mData.mMagic);
    mData.mStealth = htole32(mData.mStealth);
    for (size_t i = 0; i < 6; i++)
        mData.mAttack[i] = htole32(mData.mAttack[i]);
    mData.mGold = htole32(mData.mGold);
    esm.writeHNT("NPDT", mData, 96);

    mFlags = htole32(mFlags);
    esm.writeHNT("FLAG", mFlags);

    if (mScale != 1.0) {
        mScale = htole_float(mScale);
        esm.writeHNT("XSCL", mScale);
    }

    mInventory.save(esm);
    mSpells.save(esm);
    if (mHasAI) {
        esm.writeHNT("AIDT", mAiData, sizeof(mAiData));
    }
    mAiPackage.save(esm);
}

}
