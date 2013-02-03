#include "loadfact.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Faction::load(ESMReader &esm)
{
    mName = esm.getHNString("FNAM");

    // Read rank names. These are optional.
    int i = 0;
    while (esm.isNextSub("RNAM") && i < 10)
        mRanks[i++] = esm.getHString();

    // Main data struct
    esm.getHNT(mData, "FADT", 240);

    // Perform byte-swapping
    mData.mAttribute1 = le32toh(mData.mAttribute1);
    mData.mAttribute2 = le32toh(mData.mAttribute2);
    for (size_t i = 0; i < 10; i++)
    {
        mData.mRankData[i].mAttribute1 = le32toh(mData.mRankData[i].mAttribute1);
        mData.mRankData[i].mAttribute2 = le32toh(mData.mRankData[i].mAttribute2);
        mData.mRankData[i].mSkill1 = le32toh(mData.mRankData[i].mSkill1);
        mData.mRankData[i].mSkill2 = le32toh(mData.mRankData[i].mSkill2);
        mData.mRankData[i].mFactReaction = le32toh(mData.mRankData[i].mFactReaction);
    }
    for (size_t i = 0; i < 6; i++)
        mData.mSkillID[i] = le32toh(mData.mSkillID[i]);
    mData.mUnknown = le32toh(mData.mUnknown);
    mData.mIsHidden = le32toh(mData.mIsHidden);

    if (mData.mIsHidden > 1)
        esm.fail("Unknown flag!");

    // Read faction response values
    while (esm.hasMoreSubs())
    {
        Reaction r;
        r.mFaction = esm.getHNString("ANAM");
        esm.getHNT(r.mReaction, "INTV");
        r.mReaction = le32toh(r.mReaction);
        mReactions.push_back(r);
    }
}
void Faction::save(ESMWriter &esm)
{
    esm.writeHNCString("FNAM", mName);

    for (int i = 0; i < 10; i++)
    {
        if (mRanks[i].empty())
            break;

        esm.writeHNString("RNAM", mRanks[i], 32);
    }

    // Perform byte-swapping
    mData.mAttribute1 = htole32(mData.mAttribute1);
    mData.mAttribute2 = htole32(mData.mAttribute2);
    for (size_t i = 0; i < 10; i++)
    {
        mData.mRankData[i].mAttribute1 = htole32(mData.mRankData[i].mAttribute1);
        mData.mRankData[i].mAttribute2 = htole32(mData.mRankData[i].mAttribute2);
        mData.mRankData[i].mSkill1 = htole32(mData.mRankData[i].mSkill1);
        mData.mRankData[i].mSkill2 = htole32(mData.mRankData[i].mSkill2);
        mData.mRankData[i].mFactReaction = htole32(mData.mRankData[i].mFactReaction);
    }
    for (size_t i = 0; i < 6; i++)
        mData.mSkillID[i] = htole32(mData.mSkillID[i]);
    mData.mUnknown = htole32(mData.mUnknown);
    mData.mIsHidden = htole32(mData.mIsHidden);

    esm.writeHNT("FADT", mData, 240);

    for (std::vector<Reaction>::iterator it = mReactions.begin(); it != mReactions.end(); ++it)
    {
        esm.writeHNString("ANAM", it->mFaction);
        it->mReaction = htole32(it->mReaction);
        esm.writeHNT("INTV", it->mReaction);
    }
}

}
