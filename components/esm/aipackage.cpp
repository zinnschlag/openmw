/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

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
            if (esm.retSubName() == 0x54444e43) { // CNDT
                mList.back().mCellName = esm.getHString();
            } else if (esm.retSubName() == AI_Wander) {
                pack.mType = AI_Wander;
                esm.getHExact(&pack.mWander, 14);
                mList.push_back(pack);
            } else if (esm.retSubName() == AI_Travel) {
                pack.mType = AI_Travel;
                esm.getHExact(&pack.mTravel, 16);
                mList.push_back(pack);
            } else if (esm.retSubName() == AI_Escort ||
                       esm.retSubName() == AI_Follow)
            {
                pack.mType =
                    (esm.retSubName() == AI_Escort) ? AI_Escort : AI_Follow;
                    esm.getHExact(&pack.mTarget, 48);
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
                esm.writeHNT("AI_W", it->mWander, sizeof(it->mWander));
                break;

            case AI_Travel:
                esm.writeHNT("AI_T", it->mTravel, sizeof(it->mTravel));
                break;

            case AI_Activate:
                esm.writeHNT("AI_A", it->mActivate, sizeof(it->mActivate));
                break;

            case AI_Escort:
            case AI_Follow: {
                const char *name = (it->mType == AI_Escort) ? "AI_E" : "AI_F";
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
