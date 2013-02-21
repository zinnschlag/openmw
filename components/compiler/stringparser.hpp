/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COMPILER_STRINGPARSER_H_INCLUDED
#define COMPILER_STRINGPARSER_H_INCLUDED

#include <vector>

#include <components/interpreter/types.hpp>

#include "parser.hpp"

namespace Compiler
{
    class Literals;
    
    class StringParser : public Parser
    {
            enum State
            {
                StartState, CommaState
            };
    
            Literals& mLiterals;
            State mState;
            std::vector<Interpreter::Type_Code> mCode;
            bool mSmashCase;
                
        public:
        
            StringParser (ErrorHandler& errorHandler, Context& context, Literals& literals);

            virtual bool parseName (const std::string& name, const TokenLoc& loc,
                Scanner& scanner);
            ///< Handle a name token.
            /// \return fetch another token?

            virtual bool parseSpecial (int code, const TokenLoc& loc, Scanner& scanner);
            ///< Handle a special character token.
            /// \return fetch another token?
            
            void append (std::vector<Interpreter::Type_Code>& code);
            ///< Append code for parsed string.
            
            void smashCase();
            ///< Transform all scanned strings to lower case
            
            void reset();
            ///< Reset parser to clean state (this includes the smashCase function).    
    };
}

#endif
