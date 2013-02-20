/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COMPILER_TOKENLOC_H_INCLUDED
#define COMPILER_TOKENLOC_H_INCLUDED

#include <string>

namespace Compiler
{
    /// \brief Location of a token in a source file

    struct TokenLoc
    {
        int mColumn;
        int mLine;
        std::string mLiteral;

        TokenLoc() : mColumn (0), mLine (0), mLiteral ("") {}
    };
}

#endif // TOKENLOC_H_INCLUDED
