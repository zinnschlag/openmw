#include "loadappa.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{
void Apparatus::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mName = esm.getHNString("FNAM");

    esm.getHNT(mData, "AADT", 16);
    mData.mType = le32toh(mData.mType);
    mData.mQuality = letoh_float(mData.mQuality);
    mData.mWeight = letoh_float(mData.mWeight);
    mData.mValue = le32toh(mData.mValue);

    mScript = esm.getHNOString("SCRI");
    mIcon = esm.getHNString("ITEX");
}
void Apparatus::save(ESMWriter &esm)
{
    esm.writeHNCString("MODL", mModel);
    esm.writeHNCString("FNAM", mName);

    mData.mType = htole32(mData.mType);
    mData.mQuality = htole_float(mData.mQuality);
    mData.mWeight = htole_float(mData.mWeight);
    mData.mValue = htole32(mData.mValue);
    esm.writeHNT("AADT", mData, 16);

    esm.writeHNOCString("SCRI", mScript);
    esm.writeHNCString("ITEX", mIcon);
}
}
