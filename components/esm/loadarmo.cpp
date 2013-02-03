#include "loadarmo.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void PartReferenceList::load(ESMReader &esm)
{
    while (esm.isNextSub("INDX"))
    {
        PartReference pr;
        esm.getHT(pr.mPart); // The INDX byte
        pr.mMale = esm.getHNOString("BNAM");
        pr.mFemale = esm.getHNOString("CNAM");
        mParts.push_back(pr);
    }
}

void PartReferenceList::save(ESMWriter &esm)
{
    for (std::vector<PartReference>::iterator it = mParts.begin(); it != mParts.end(); ++it)
    {
        esm.writeHNT("INDX", it->mPart);
        esm.writeHNOString("BNAM", it->mMale);
        esm.writeHNOString("CNAM", it->mFemale);
    }
}

void Armor::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mName = esm.getHNString("FNAM");
    mScript = esm.getHNOString("SCRI");

    esm.getHNT(mData, "AODT", 24);
    mData.mType = le32toh(mData.mType);
    mData.mWeight = letoh_float(mData.mWeight);
    mData.mValue = le32toh(mData.mValue);
    mData.mHealth = le32toh(mData.mHealth);
    mData.mEnchant = le32toh(mData.mEnchant);
    mData.mArmor = le32toh(mData.mArmor);

    mIcon = esm.getHNOString("ITEX");
    mParts.load(esm);
    mEnchant = esm.getHNOString("ENAM");
}

void Armor::save(ESMWriter &esm)
{
    esm.writeHNCString("MODL", mModel);
    esm.writeHNCString("FNAM", mName);
    esm.writeHNOCString("SCRI", mScript);

    mData.mType = htole32(mData.mType);
    mData.mWeight = htole_float(mData.mWeight);
    mData.mValue = htole32(mData.mValue);
    mData.mHealth = htole32(mData.mHealth);
    mData.mEnchant = htole32(mData.mEnchant);
    mData.mArmor = htole32(mData.mArmor);
    esm.writeHNT("AODT", mData, 24);

    esm.writeHNOCString("ITEX", mIcon);
    mParts.save(esm);
    esm.writeHNOCString("ENAM", mEnchant);
}

}
