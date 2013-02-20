/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWMECHANICS_MOVEMENT_H
#define GAME_MWMECHANICS_MOVEMENT_H

namespace MWMechanics
{
    /// Desired movement for an actor
    struct Movement
    {
        signed char mLeftRight; // 1: wants to move left, -1: wants to move right
        signed char mForwardBackward; // 1:wants to move forward, -1: wants to move backward
		signed char mUpDown;

        Movement() : mLeftRight (0), mForwardBackward (0), mUpDown(0) {}
    };
}

#endif
