/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWMECHANICS_DRAWSTATE_H
#define GAME_MWMECHANICS_DRAWSTATE_H

namespace MWMechanics
{
    /// \note The _ suffix is required to avoid a collision with a Windoze macro. Die, Microsoft! Die!
    enum DrawState_
    {
        DrawState_Weapon = 0,
        DrawState_Spell = 1,
        DrawState_Nothing = 2
    };
}

#endif
