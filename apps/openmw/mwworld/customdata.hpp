/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWWORLD_CUSTOMDATA_H
#define GAME_MWWORLD_CUSTOMDATA_H

namespace MWWorld
{
    /// \brief Base class for the MW-class-specific part of RefData
    class CustomData
    {
        public:

            virtual ~CustomData() {}

            virtual CustomData *clone() const = 0;
    };
}

#endif
