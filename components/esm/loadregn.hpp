#ifndef _ESM_REGN_H
#define _ESM_REGN_H

#include <string>
#include <vector>

#include "record.hpp"
#include "esm_common.hpp"

namespace ESM
{

/*
 * Region data
 */

struct Region : public Record
{
#pragma pack(push)
#pragma pack(1)
    struct WEATstruct
    {
        // I guess these are probabilities
        char mClear, mCloudy, mFoggy, mOvercast, mRain, mThunder, mAsh, mBlight,
        // Unknown weather, probably snow and something. Only
        // present in file version 1.3.
                mA, mB;
    }; // 10 bytes

    // Reference to a sound that is played randomly in this region
    struct SoundRef
    {
        NAME32 mSound;
        char mChance;
    }; // 33 bytes
#pragma pack(pop)

    WEATstruct mData;
    int mMapColor; // RGBA

    // sleepList refers to a eveled list of creatures you can meet if
    // you sleep outside in this region.
    std::string mName, mSleepList;

    std::vector<SoundRef> mSoundList;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);

    int getName() { return REC_REGN; }
};
}
#endif
