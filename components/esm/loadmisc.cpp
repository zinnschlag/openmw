#include "loadmisc.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Miscellaneous::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mName = esm.getHNOString("FNAM");

    esm.getHNT(mData, "MCDT", 12);
    mData.mWeight = letoh_float(mData.mWeight);
    mData.mValue = le32toh(mData.mValue);
    mData.mIsKey = le32toh(mData.mIsKey);

    mScript = esm.getHNOString("SCRI");
    mIcon = esm.getHNOString("ITEX");
}
void Miscellaneous::save(ESMWriter &esm)
{
    esm.writeHNCString("MODL", mModel);
    esm.writeHNOCString("FNAM", mName);

    mData.mWeight = htole_float(mData.mWeight);
    mData.mValue = htole32(mData.mValue);
    mData.mIsKey = htole32(mData.mIsKey);
    esm.writeHNT("MCDT", mData, 12);

    esm.writeHNOCString("SCRI", mScript);
    esm.writeHNOCString("ITEX", mIcon);
}

}
