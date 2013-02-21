/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "errorhandler.hpp"

namespace Compiler
{
    // constructor

    ErrorHandler::ErrorHandler() : mWarnings (0), mErrors (0) {}

    // destructor

    ErrorHandler::~ErrorHandler() {}

    // Was compiling successful?

    bool ErrorHandler::isGood() const
    {
        return mErrors==0;
    }

    // Return number of errors

    int ErrorHandler::countErrors() const
    {
        return mErrors;
    }

    // Return number of warnings

    int ErrorHandler::countWarnings() const
    {
        return mWarnings;
    }

    // Generate a warning message.

    void ErrorHandler::warning (const std::string& message, const TokenLoc& loc)
    {
        ++mWarnings;
        report (message, loc, WarningMessage);
    }

    // Generate an error message.

    void ErrorHandler::error (const std::string& message, const TokenLoc& loc)
    {
        ++mErrors;
        report (message, loc, ErrorMessage);
    }

    // Generate an error message for an unexpected EOF.

    void ErrorHandler::endOfFile()
    {
        ++mErrors;
        report ("unexpected end of file", ErrorMessage);
    }

    // Remove all previous error/warning events

    void ErrorHandler::reset()
    {
        mErrors = mWarnings = 0;
    }
}
