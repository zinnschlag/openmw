/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "streamerrorhandler.hpp"

#include "tokenloc.hpp"

namespace Compiler
{
    // Report error to the user.

    void StreamErrorHandler::report (const std::string& message, const TokenLoc& loc,
        Type type)
    {
        if (type==ErrorMessage)
            mStream << "error ";
        else
            mStream << "warning ";

        mStream
            << "line " << loc.mLine << ", column " << loc.mColumn
            << " (" << loc.mLiteral << ")" << std::endl
            << "    " << message << std::endl;
    }

    // Report a file related error

    void StreamErrorHandler::report (const std::string& message, Type type)
    {
        if (type==ErrorMessage)
            mStream << "error ";
        else
            mStream << "warning ";

        mStream
            << "file:" << std::endl
            << "    " << message << std::endl;
    }

    StreamErrorHandler::StreamErrorHandler (std::ostream& ErrorStream) : mStream (ErrorStream) {}
}
