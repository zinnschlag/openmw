#include "loadligh.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Light::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mName = esm.getHNOString("FNAM");
    mIcon = esm.getHNOString("ITEX");

    assert(sizeof(mData) == 24);
    esm.getHNT(mData, "LHDT", 24);
    mData.mWeight = letoh_float(mData.mWeight);
    mData.mValue = le32toh(mData.mValue);
    mData.mTime = le32toh(mData.mTime);
    mData.mRadius = le32toh(mData.mRadius);
    mData.mColor = le32toh(mData.mColor);
    mData.mFlags = le32toh(mData.mFlags);

    mScript = esm.getHNOString("SCRI");
    mSound = esm.getHNOString("SNAM");
}
void Light::save(ESMWriter &esm)
{
    esm.writeHNCString("MODL", mModel);
    esm.writeHNOCString("FNAM", mName);
    esm.writeHNOCString("ITEX", mIcon);

    mData.mWeight = htole_float(mData.mWeight);
    mData.mValue = htole32(mData.mValue);
    mData.mTime = htole32(mData.mTime);
    mData.mRadius = htole32(mData.mRadius);
    mData.mColor = htole32(mData.mColor);
    mData.mFlags = htole32(mData.mFlags);
    esm.writeHNT("LHDT", mData, 24);

    esm.writeHNOCString("SCRI", mScript);
    esm.writeHNOCString("SNAM", mSound);
}

}
