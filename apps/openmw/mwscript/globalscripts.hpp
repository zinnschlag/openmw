/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_SCRIPT_GLOBALSCRIPTS_H
#define GAME_SCRIPT_GLOBALSCRIPTS_H

#include <string>
#include <map>

#include "locals.hpp"

namespace MWWorld 
{
    struct ESMStore;
}

namespace MWScript
{
    class GlobalScripts
    {
            const MWWorld::ESMStore& mStore;
            std::map<std::string, std::pair<bool, Locals> > mScripts; // running, local variables

        public:

            GlobalScripts (const MWWorld::ESMStore& store);

            void addScript (const std::string& name);

            void removeScript (const std::string& name);

            bool isRunning (const std::string& name) const;

            void run();
            ///< run all active global scripts
    };
}

#endif
