#include "loadalch.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{
void Potion::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mIcon = esm.getHNOString("TEXT"); // not ITEX here for some reason
    mScript = esm.getHNOString("SCRI");
    mName = esm.getHNOString("FNAM");

    esm.getHNT(mData, "ALDT", 12);
    mData.mWeight = letoh_float(mData.mWeight);
    mData.mValue = le32toh(mData.mValue);
    mData.mAutoCalc = le32toh(mData.mAutoCalc);

    mEffects.load(esm);
}

void Potion::save(ESMWriter &esm)
{
    esm.writeHNCString("MODL", mModel);
    esm.writeHNOCString("TEXT", mIcon);
    esm.writeHNOCString("SCRI", mScript);
    esm.writeHNOCString("FNAM", mName);

    mData.mWeight = htole_float(mData.mWeight);
    mData.mValue = htole32(mData.mValue);
    mData.mAutoCalc = htole32(mData.mAutoCalc);
    esm.writeHNT("ALDT", mData, 12);

    mEffects.save(esm);
}
}
