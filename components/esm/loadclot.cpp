#include "loadclot.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Clothing::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mName = esm.getHNOString("FNAM");
    esm.getHNT(mData, "CTDT", 12);
    mData.mType = le32toh(mData.mType);
    mData.mWeight = letoh_float(mData.mWeight);
    mData.mValue = le16toh(mData.mValue);
    mData.mEnchant = le16toh(mData.mEnchant);

    mScript = esm.getHNOString("SCRI");
    mIcon = esm.getHNOString("ITEX");

    mParts.load(esm);

    mEnchant = esm.getHNOString("ENAM");
}
void Clothing::save(ESMWriter &esm)
{
    esm.writeHNCString("MODL", mModel);
    esm.writeHNOCString("FNAM", mName);

    mData.mType = htole32(mData.mType);
    mData.mWeight = htole_float(mData.mWeight);
    mData.mValue = htole16(mData.mValue);
    mData.mEnchant = htole16(mData.mEnchant);
    esm.writeHNT("CTDT", mData, 12);

    esm.writeHNOCString("SCRI", mScript);
    esm.writeHNOCString("ITEX", mIcon);

    mParts.save(esm);

    esm.writeHNOCString("ENAM", mEnchant);
}

}
