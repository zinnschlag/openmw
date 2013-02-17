#include "loadlocks.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

template<typename T>
void Tool<T>::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mName = esm.getHNString("FNAM");

    esm.getSubName();
    NAME n = esm.retSubName();
    // The data name varies, RIDT for repair items, LKDT for lock
    // picks, PBDT for probes

    esm.getHT(mData, 16);

    if (n == "RIDT")
    {
        mType = Type_Repair;
        // Swap t.data.quality and t.data.uses for repair items (sigh)
        T tmp = mData.mUses;
        mData.mUses = mData.mQuality;
        mData.mQuality = tmp;
    }
    else if (n == "LKDT")
        mType = Type_Pick;
    else if (n == "PBDT")
        mType = Type_Probe;

    mScript = esm.getHNOString("SCRI");
    mIcon = esm.getHNOString("ITEX");
}

template<typename T>
void Tool<T>::save(ESMWriter &esm)
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
    
    Data<T> write = mData;
    if (mType == Type_Repair)
    {
        T tmp = write.mUses;
        write.mUses = write.mQuality;
        write.mQuality = tmp;
    }

    esm.writeHNT(typeName, write, 16);
    esm.writeHNOString("SCRI", mScript);
    esm.writeHNOCString("ITEX", mIcon);
}

}  // namespace ESM

template class ESM::Tool<int>;
template class ESM::Tool<float>;
