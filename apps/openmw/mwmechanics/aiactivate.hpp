/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWMECHANICS_AIACTIVATE_H
#define GAME_MWMECHANICS_AIACTIVATE_H

#include "aipackage.hpp"
#include <string>

namespace MWMechanics
{

    class AiActivate : public AiPackage
    {
        public:
            AiActivate(const std::string &objectId);
            virtual AiActivate *clone() const;
            virtual bool execute (const MWWorld::Ptr& actor);
                    ///< \return Package completed?
            virtual int getTypeId() const;

        private:
            std::string mObjectId;
    };
}
#endif // GAME_MWMECHANICS_AIACTIVATE_H
