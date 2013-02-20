/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COMPILER_LITERALS_H_INCLUDED
#define COMPILER_LITERALS_H_INCLUDED

#include <string>
#include <vector>

#include <components/interpreter/types.hpp>

namespace Compiler
{
    /// \brief Literal values.
    
    class Literals
    {
            std::vector<Interpreter::Type_Integer> mIntegers;
            std::vector<Interpreter::Type_Float> mFloats;
            std::vector<std::string> mStrings;
    
        public:
        
            int getIntegerSize() const;
            ///< Return size of integer block (in bytes).

            int getFloatSize() const;
            ///< Return size of float block (in bytes).
        
            int getStringSize() const;
            ///< Return size of string block (in bytes).
        
            void append (std::vector<Interpreter::Type_Code>& code) const;
            ///< Apepnd literal blocks to code.
            /// \note code blocks will be padded for 32-bit alignment.
        
            int addInteger (Interpreter::Type_Integer value);
            ///< add integer liternal and return index.
            
            int addFloat (Interpreter::Type_Float value);
            ///< add float literal and return value.
            
            int addString (const std::string& value);
            ///< add string literal and return value.
        
            void clear();
            ///< remove all literals.
    };
}

#endif

