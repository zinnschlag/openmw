/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_SCRIPT_LOCALS_H
#define GAME_SCRIPT_LOCALS_H

#include <vector>

#include <components/esm/loadscpt.hpp>
#include <components/interpreter/types.hpp>

namespace MWScript
{
    class Locals
    {
        public:
            std::vector<Interpreter::Type_Short> mShorts;
            std::vector<Interpreter::Type_Integer> mLongs;
            std::vector<Interpreter::Type_Float> mFloats;
            
            void configure (const ESM::Script& script);
            bool setVarByInt(const std::string& script, const std::string& var, int val);
        
    };
}

#endif

