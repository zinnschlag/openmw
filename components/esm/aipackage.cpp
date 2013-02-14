#include "aipackage.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{
    void AIPackageList::load(ESMReader &esm)
    {
        while (esm.hasMoreSubs()) {
            // initialize every iteration
            AIPackage pack;

            esm.getSubName();
            if (esm.retSubName() == REC_CNDT) {
                mList.back().mCellName = esm.getHString();
            } else if (esm.retSubName() == AI_Wander) {
                pack.mType = AI_Wander;
                esm.getHExact(&pack.mWander, 14);
                pack.mWander.mDistance = le16toh(pack.mWander.mDistance);
                pack.mWander.mDuration = le16toh(pack.mWander.mDuration);
                mList.push_back(pack);
            } else if (esm.retSubName() == AI_Travel) {
                pack.mType = AI_Travel;
                esm.getHExact(&pack.mTravel, 16);
                pack.mTravel.mX = letoh_float(pack.mTravel.mX);
                pack.mTravel.mY = letoh_float(pack.mTravel.mY);
                pack.mTravel.mZ = letoh_float(pack.mTravel.mZ);
                pack.mTravel.mUnk = le32toh(pack.mTravel.mUnk);
                mList.push_back(pack);
            } else if (esm.retSubName() == AI_Escort ||
                       esm.retSubName() == AI_Follow)
            {
                pack.mType =
                    (esm.retSubName() == AI_Escort) ? AI_Escort : AI_Follow;
                esm.getHExact(&pack.mTarget, 48);
                pack.mTarget.mX = letoh_float(pack.mTarget.mX);
                pack.mTarget.mY = letoh_float(pack.mTarget.mY);
                pack.mTarget.mZ = letoh_float(pack.mTarget.mZ);
                pack.mTarget.mDuration = le16toh(pack.mTarget.mDuration);
                pack.mTarget.mUnk = le16toh(pack.mTarget.mUnk);
                mList.push_back(pack);
            } else if (esm.retSubName() == AI_Activate) {
                pack.mType = AI_Activate;
                esm.getHExact(&pack.mActivate, 33);
                mList.push_back(pack);
            } else { // not AI package related data, so leave
                 return;
            }
        }
    }

    void AIPackageList::save(ESMWriter &esm)
    {
        typedef std::vector<AIPackage>::iterator PackageIter;
        for (PackageIter it = mList.begin(); it != mList.end(); ++it) {
            switch (it->mType) {
            case AI_Wander:
                it->mWander.mDistance = htole16(it->mWander.mDistance);
                it->mWander.mDuration = htole16(it->mWander.mDuration);
                esm.writeHNT("AI_W", it->mWander, sizeof(it->mWander));
                break;

            case AI_Travel:
                it->mTravel.mX = htole_float(it->mTravel.mX);
                it->mTravel.mY = htole_float(it->mTravel.mY);
                it->mTravel.mZ = htole_float(it->mTravel.mZ);
                it->mTravel.mUnk = htole32(it->mTravel.mUnk);
                esm.writeHNT("AI_T", it->mTravel, sizeof(it->mTravel));
                break;

            case AI_Activate:
                esm.writeHNT("AI_A", it->mActivate, sizeof(it->mActivate));
                break;

            case AI_Escort:
            case AI_Follow: {
                const char *name = (it->mType == AI_Escort) ? "AI_E" : "AI_F";
                it->mTarget.mX = htole_float(it->mTarget.mX);
                it->mTarget.mY = htole_float(it->mTarget.mY);
                it->mTarget.mZ = htole_float(it->mTarget.mZ);
                it->mTarget.mDuration = htole16(it->mTarget.mDuration);
                it->mTarget.mUnk = htole16(it->mTarget.mUnk);
                esm.writeHNT(name, it->mTarget, sizeof(it->mTarget));
                esm.writeHNOCString("CNDT", it->mCellName);
                break;
            }

            default:
                break;
            }
        }
    }
}
