/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COMPILER_OUTPUT_H_INCLUDED
#define COMPILER_OUTPUT_H_INCLUDED

#include "literals.hpp"

#include <vector>

#include <components/interpreter/types.hpp>

namespace Compiler
{
    class Locals;

    class Output
    {
            Literals mLiterals;
            std::vector<Interpreter::Type_Code> mCode;            
            Locals& mLocals;
                
        public:
        
            Output (Locals& locals);
    
            void getCode (std::vector<Interpreter::Type_Code>& code) const;
            ///< store generated code in \æ code.

            const Literals& getLiterals() const;

            const Locals& getLocals() const;
            
            const std::vector<Interpreter::Type_Code>& getCode() const;
            
            Literals& getLiterals();

            std::vector<Interpreter::Type_Code>& getCode();
            
            Locals& getLocals();
            
            void clear();
    };
}

#endif

