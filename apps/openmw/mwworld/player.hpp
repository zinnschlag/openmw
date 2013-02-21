/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWWORLD_PLAYER_H
#define GAME_MWWORLD_PLAYER_H

#include "../mwworld/cellstore.hpp"
#include "../mwworld/refdata.hpp"
#include "../mwworld/ptr.hpp"

#include "../mwmechanics/drawstate.hpp"

namespace MWBase
{
    class World;
}

namespace MWWorld
{
    class CellStore;

    /// \brief NPC object representing the player and additional player data
    class Player
    {
        LiveCellRef<ESM::NPC>   mPlayer;
        MWWorld::CellStore      *mCellStore;
        std::string             mSign;

        bool                    mAutoMove;
        int                     mForwardBackward;

    public:

        Player(const ESM::NPC *player, const MWBase::World& world);

        void setCell (MWWorld::CellStore *cellStore)
        {
            mCellStore = cellStore;
        }

        MWWorld::Ptr getPlayer()
        {
            MWWorld::Ptr ptr (&mPlayer, mCellStore);
            return ptr;
        }

        void setBirthSign(const std::string &sign) {
            mSign = sign;
        }

        const std::string &getBirthSign() const {
            return mSign;
        }

        void setDrawState (MWMechanics::DrawState_ state);

        bool getAutoMove() const
        {
            return mAutoMove;
        }

        MWMechanics::DrawState_ getDrawState(); /// \todo constness

        void setAutoMove (bool enable);

        void setLeftRight (int value);

        void setForwardBackward (int value);
        void setUpDown(int value);

        void toggleRunning();
    };
}
#endif
