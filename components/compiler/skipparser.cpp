/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "skipparser.hpp"

#include "scanner.hpp"

namespace Compiler
{
    SkipParser::SkipParser (ErrorHandler& errorHandler, Context& context)
    : Parser (errorHandler, context)
    {}

    bool SkipParser::parseInt (int value, const TokenLoc& loc, Scanner& scanner)
    {
        return true;
    }

    bool SkipParser::parseFloat (float value, const TokenLoc& loc, Scanner& scanner)
    {
        return true;
    }

    bool SkipParser::parseName (const std::string& name, const TokenLoc& loc,
        Scanner& scanner)
    {
        return true;
    }

    bool SkipParser::parseKeyword (int keyword, const TokenLoc& loc, Scanner& scanner)
    {
        return true;
    }

    bool SkipParser::parseSpecial (int code, const TokenLoc& loc, Scanner& scanner)
    {
        if (code==Scanner::S_newline)
            return false;
            
        return true;
    }
}

