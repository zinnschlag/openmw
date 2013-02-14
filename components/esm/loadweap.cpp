#include "loadweap.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Weapon::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mName = esm.getHNOString("FNAM");

    esm.getHNT(mData, "WPDT", 32);
    mData.mWeight = letoh_float(mData.mWeight);
    mData.mValue = le32toh(mData.mValue);
    mData.mType = le16toh(mData.mType);
    mData.mHealth = le16toh(mData.mHealth);
    mData.mSpeed = letoh_float(mData.mSpeed);
    mData.mReach = letoh_float(mData.mReach);
    mData.mEnchant = le16toh(mData.mEnchant);
    mData.mFlags = le32toh(mData.mFlags);

    mScript = esm.getHNOString("SCRI");
    mIcon = esm.getHNOString("ITEX");
    mEnchant = esm.getHNOString("ENAM");
}
void Weapon::save(ESMWriter &esm)
{
    esm.writeHNCString("MODL", mModel);
    esm.writeHNOCString("FNAM", mName);

    mData.mWeight = htole_float(mData.mWeight);
    mData.mValue = htole32(mData.mValue);
    mData.mType = htole16(mData.mType);
    mData.mHealth = htole16(mData.mHealth);
    mData.mSpeed = htole_float(mData.mSpeed);
    mData.mReach = htole_float(mData.mReach);
    mData.mEnchant = htole16(mData.mEnchant);
    mData.mFlags = htole32(mData.mFlags);
    esm.writeHNT("WPDT", mData, 32);

    esm.writeHNOCString("SCRI", mScript);
    esm.writeHNOCString("ITEX", mIcon);
    esm.writeHNOCString("ENAM", mEnchant);
}

}
