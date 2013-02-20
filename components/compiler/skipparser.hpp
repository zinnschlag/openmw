/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COMPILER_SKIPPARSER_H_INCLUDED
#define COMPILER_SKIPPARSER_H_INCLUDED

#include "parser.hpp"

namespace Compiler
{
    // \brief Skip parser for skipping a line
    //
    // This parser is mainly intended for skipping the rest of a faulty line.
    
    class SkipParser : public Parser
    {
        public:
           
            SkipParser (ErrorHandler& errorHandler, Context& context);
    
            virtual bool parseInt (int value, const TokenLoc& loc, Scanner& scanner);
            ///< Handle an int token.
            /// \return fetch another token?

            virtual bool parseFloat (float value, const TokenLoc& loc, Scanner& scanner);
            ///< Handle a float token.
            /// \return fetch another token?

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
    };
}

#endif

