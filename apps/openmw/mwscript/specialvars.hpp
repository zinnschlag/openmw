#ifndef SPECIAL_VARS_H
#define SPECIAL_VARS_H

#include <vector>

#include <components/interpreter/types.hpp>

#include "../mwworld/ptr.hpp"

namespace MWScript
{
    struct SpecialVars
    {   
        // Set by game
        //std::vector<MWWorld::Ptr> mOnPCAdd;
        //std::vector<MWWorld::Ptr> mOnPCDrop;
        std::vector<MWWorld::Ptr> mOnPCEquip;
        //std::vector<MWWorld::Ptr> mOnPCHitMe;
        //std::vector<MWWorld::Ptr> mOnPCRepair;
        //std::vector<MWWorld::Ptr> mOnPCSoulGemUse;
        //??? mMinimumProfit;

        // Flags
        //??? mCompanion;
        //??? mPCSkipEquip;

        SpecialVars()
        {
            mOnPCEquip = std::vector<MWWorld::Ptr>();
        }
    };
}

#endif
