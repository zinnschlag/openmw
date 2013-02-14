#include "loadench.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Enchantment::load(ESMReader &esm)
{
    esm.getHNT(mData, "ENDT", 16);
    mData.mType = le32toh(mData.mType);
    mData.mCost = le32toh(mData.mCost);
    mData.mCharge = le32toh(mData.mCharge);
    mData.mAutocalc = le32toh(mData.mAutocalc);
    mEffects.load(esm);
}

void Enchantment::save(ESMWriter &esm)
{
    mData.mType = htole32(mData.mType);
    mData.mCost = htole32(mData.mCost);
    mData.mCharge = htole32(mData.mCharge);
    mData.mAutocalc = htole32(mData.mAutocalc);
    esm.writeHNT("ENDT", mData, 16);
    mEffects.save(esm);
}

}
