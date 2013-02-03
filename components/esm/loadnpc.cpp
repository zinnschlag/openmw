#include "loadnpc.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void NPC::load(ESMReader &esm)
{
    mNpdt52.mGold = -10;

    mModel = esm.getHNOString("MODL");
    mName = esm.getHNOString("FNAM");

    mRace = esm.getHNString("RNAM");
    mClass = esm.getHNString("CNAM");
    mFaction = esm.getHNString("ANAM");
    mHead = esm.getHNString("BNAM");
    mHair = esm.getHNString("KNAM");

    mScript = esm.getHNOString("SCRI");

    esm.getSubNameIs("NPDT");
    esm.getSubHeader();
    if (esm.getSubSize() == 52)
    {
        mNpdtType = 52;
        esm.getExact(&mNpdt52, 52);
        mNpdt52.mLevel = le16toh(mNpdt52.mLevel);
        mNpdt52.mHealth = le16toh(mNpdt52.mHealth);
        mNpdt52.mMana = le16toh(mNpdt52.mMana);
        mNpdt52.mFatigue = le16toh(mNpdt52.mFatigue);
        mNpdt52.mGold = le32toh(mNpdt52.mGold);
    }
    else if (esm.getSubSize() == 12)
    {
        mNpdtType = 12;
        esm.getExact(&mNpdt12, 12);
        mNpdt12.mLevel = le16toh(mNpdt12.mLevel);
        mNpdt12.mGold = le32toh(mNpdt12.mGold);
    }
    else
        esm.fail("NPC_NPDT must be 12 or 52 bytes long");

    esm.getHNT(mFlags, "FLAG");
    mFlags = le32toh(mFlags);

    mInventory.load(esm);
    mSpells.load(esm);

    if (esm.isNextSub("AIDT"))
    {
        esm.getHExact(&mAiData, sizeof(mAiData));
        mAiData.mServices = le32toh(mAiData.mServices);
        mHasAI= true;
    }
    else
        mHasAI = false;

    while (esm.isNextSub("DODT") || esm.isNextSub("DNAM")) {
        if (esm.retSubName() == REC_DODT) {
            Dest dodt;
            esm.getHExact(&dodt.mPos, 24);
            for (size_t i = 0; i < 3; i++)
                dodt.mPos.pos[i] = htole_float(dodt.mPos.pos[i]);
            for (size_t i = 0; i < 3; i++)
                dodt.mPos.rot[i] = htole_float(dodt.mPos.rot[i]);
            mTransport.push_back(dodt);
        } else if (esm.retSubName() == REC_DNAM) {
            mTransport.back().mCellName = esm.getHString();
        }
    }

    mAiPackage.load(esm);
    esm.skipRecord();
}
void NPC::save(ESMWriter &esm)
{
    esm.writeHNOCString("MODL", mModel);
    esm.writeHNOCString("FNAM", mName);
    esm.writeHNCString("RNAM", mRace);
    esm.writeHNCString("CNAM", mClass);
    esm.writeHNCString("ANAM", mFaction);
    esm.writeHNCString("BNAM", mHead);
    esm.writeHNCString("KNAM", mHair);
    esm.writeHNOCString("SCRI", mScript);

    if (mNpdtType == 52)
    {
        mNpdt52.mLevel = htole16(mNpdt52.mLevel);
        mNpdt52.mHealth = htole16(mNpdt52.mHealth);
        mNpdt52.mMana = htole16(mNpdt52.mMana);
        mNpdt52.mFatigue = htole16(mNpdt52.mFatigue);
        mNpdt52.mGold = htole32(mNpdt52.mGold);
        esm.writeHNT("NPDT", mNpdt52, 52);
    }
    else if (mNpdtType == 12)
    {
        mNpdt12.mLevel = htole16(mNpdt12.mLevel);
        mNpdt12.mGold = htole32(mNpdt12.mGold);
        esm.writeHNT("NPDT", mNpdt12, 12);
    }

    mFlags = htole32(mFlags);
    esm.writeHNT("FLAG", mFlags);

    mInventory.save(esm);
    mSpells.save(esm);

    if (mHasAI) {
        mAiData.mServices = htole32(mAiData.mServices);
        esm.writeHNT("AIDT", mAiData, sizeof(mAiData));
    }

    typedef std::vector<Dest>::iterator DestIter;
    for (DestIter it = mTransport.begin(); it != mTransport.end(); ++it) {
        for (size_t i = 0; i < 3; i++)
            it->mPos.pos[i] = htole_float(it->mPos.pos[i]);
        for (size_t i = 0; i < 3; i++)
            it->mPos.rot[i] = htole_float(it->mPos.rot[i]);
        esm.writeHNT("DODT", it->mPos, sizeof(it->mPos));
        esm.writeHNOCString("DNAM", it->mCellName);
    }
    mAiPackage.save(esm);
}

}
