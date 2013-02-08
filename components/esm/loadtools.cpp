#include "loadtools.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Tool::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mName = esm.getHNString("FNAM");

    esm.getSubName();
    NAME n = esm.retSubName();
    // The data name varies, RIDT for repair items, LKDT for lock
    // picks, PBDT for probes

    esm.getHT(mData, 16);
    mData.mWeight = letoh_float(mData.mWeight);
    mData.mValue = le32toh(mData.mValue);
    mData.mQU1.mUses = le32toh(mData.mQU1.mUses);
    mData.mQU2.mUses = le32toh(mData.mQU2.mUses);

    if (n == "RIDT")
        mType = Type_Repair;
    else if (n == "LKDT")
        mType = Type_Pick;
    else if (n == "PBDT")
        mType = Type_Probe;

    mScript = esm.getHNOString("SCRI");
    mIcon = esm.getHNOString("ITEX");
}

void Tool::save(ESMWriter &esm)
{
    esm.writeHNCString("MODL", mModel);
    esm.writeHNCString("FNAM", mName);

    std::string typeName;
    switch(mType)
    {
    case Type_Repair: typeName = "RIDT"; break;
    case Type_Pick: typeName = "LKDT"; break;
    case Type_Probe: typeName = "PBDT"; break;
    }

    mData.mWeight = htole_float(mData.mWeight);
    mData.mValue = htole32(mData.mValue);
    mData.mQU1.mUses = htole32(mData.mQU1.mUses);
    mData.mQU2.mUses = htole32(mData.mQU2.mUses);
    esm.writeHNT(typeName, mData, 16);

    esm.writeHNOString("SCRI", mScript);
    esm.writeHNOCString("ITEX", mIcon);
}


}
