/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COMPILER_FILEPARSER_H_INCLUDED
#define COMPILER_FILEPARSER_H_INCLUDED

#include "parser.hpp"
#include "scriptparser.hpp"
#include "locals.hpp"
#include "literals.hpp"

namespace Compiler
{
    // Top-level parser, to be used for global scripts, local scripts and targeted scripts
    
    class FileParser : public Parser
    {
            enum State
            {
                BeginState, NameState, BeginCompleteState, EndNameState,
                EndCompleteState
            };
            
            ScriptParser mScriptParser;
            State mState;
            std::string mName;
            Locals mLocals;

        public:
        
            FileParser (ErrorHandler& errorHandler, Context& context);

            std::string getName() const;
            ///< Return script name.

            void getCode (std::vector<Interpreter::Type_Code>& code) const;
            ///< store generated code in \æ code.
            
            const Locals& getLocals() const;
            ///< get local variable declarations.

            virtual bool parseName (const std::string& name, const TokenLoc& loc,
                Scanner& scanner);
            ///< Handle a name token.
            /// \return fetch another token?

            virtual bool parseKeyword (int keyword, const TokenLoc& loc, Scanner& scanner);
            ///< Handle a keyword token.
            /// \return fetch another token?

            virtual bool parseSpecial (int code, const TokenLoc& loc, Scanner& scanner);
            ///< Handle a special character token.
            /// \return fetch another token?

            virtual void parseEOF (Scanner& scanner);
            ///< Handle EOF token.    
            
            void reset();
            ///< Reset parser to clean state.
    };
}

#endif
