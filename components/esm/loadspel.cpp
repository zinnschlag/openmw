#include "loadspel.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Spell::load(ESMReader &esm)
{
    mName = esm.getHNOString("FNAM");

    esm.getHNT(mData, "SPDT", 12);
    mData.mType = le32toh(mData.mType);
    mData.mCost = le32toh(mData.mCost);
    mData.mFlags = le32toh(mData.mFlags);

    mEffects.load(esm);
}

void Spell::save(ESMWriter &esm)
{
    esm.writeHNOCString("FNAM", mName);

    mData.mType = htole32(mData.mType);
    mData.mCost = htole32(mData.mCost);
    mData.mFlags = htole32(mData.mFlags);
    esm.writeHNT("SPDT", mData, 12);

    mEffects.save(esm);
}

}
