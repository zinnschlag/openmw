/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COMPILER_SCRIPTPARSER_H_INCLUDED
#define COMPILER_SCRIPTPARSER_H_INCLUDED


#include "parser.hpp"
#include "lineparser.hpp"
#include "controlparser.hpp"
#include "output.hpp"

namespace Compiler
{
    class Locals;

    // Script parser, to be used in dialogue scripts and as part of FileParser
    
    class ScriptParser : public Parser
    {
            Output mOutput;
            LineParser mLineParser;
            ControlParser mControlParser;
            bool mEnd;

        public:
        
            /// \param end of script is marked by end keyword.
            ScriptParser (ErrorHandler& errorHandler, Context& context, Locals& locals,
                bool end = false);
    
            void getCode (std::vector<Interpreter::Type_Code>& code) const;
            ///< store generated code in \æ code.
    
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

