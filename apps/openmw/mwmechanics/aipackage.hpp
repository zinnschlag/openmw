/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWMECHANICS_AIPACKAGE_H
#define GAME_MWMECHANICS_AIPACKAGE_H

namespace MWWorld
{
    class Ptr;
}

namespace MWMechanics
{
    /// \brief Base class for AI packages
    class AiPackage
    {
        public:
    
            virtual ~AiPackage();
      
            virtual AiPackage *clone() const = 0;
            
            virtual bool execute (const MWWorld::Ptr& actor) = 0;
            ///< \return Package completed?
            
            virtual int getTypeId() const = 0;
            ///< 0: Wanter, 1 Travel, 2 Escort, 3 Follow, 4 Activate
    };
}

#endif

