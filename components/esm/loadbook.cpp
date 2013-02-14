#include "loadbook.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Book::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mName = esm.getHNOString("FNAM");

    esm.getHNT(mData, "BKDT", 20);
    mData.mWeight = letoh_float(mData.mWeight);
    mData.mValue = le32toh(mData.mValue);
    mData.mIsScroll = le32toh(mData.mIsScroll);
    mData.mSkillID = le32toh(mData.mSkillID);
    mData.mEnchant = le32toh(mData.mEnchant);

    mScript = esm.getHNOString("SCRI");
    mIcon = esm.getHNOString("ITEX");
    mText = esm.getHNOString("TEXT");
    mEnchant = esm.getHNOString("ENAM");
}
void Book::save(ESMWriter &esm)
{
    esm.writeHNCString("MODL", mModel);
    esm.writeHNOCString("FNAM", mName);

    mData.mWeight = htole_float(mData.mWeight);
    mData.mValue = htole32(mData.mValue);
    mData.mIsScroll = htole32(mData.mIsScroll);
    mData.mSkillID = htole32(mData.mSkillID);
    mData.mEnchant = htole32(mData.mEnchant);
    esm.writeHNT("BKDT", mData, 20);

    esm.writeHNOCString("SCRI", mScript);
    esm.writeHNOCString("ITEX", mIcon);
    esm.writeHNOString("TEXT", mText);
    esm.writeHNOCString("ENAM", mEnchant);
}

}
