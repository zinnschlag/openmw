/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef COMPILER_STREAMERRORHANDLER_H_INCLUDED
#define COMPILER_STREAMERRORHANDLER_H_INCLUDED

#include <ostream>

#include "errorhandler.hpp"

namespace Compiler
{
    /// \brief Error handler implementation: Write errors into stream

    class StreamErrorHandler : public ErrorHandler
    {
            std::ostream& mStream;

        // not implemented

            StreamErrorHandler (const StreamErrorHandler&);
            StreamErrorHandler& operator= (const StreamErrorHandler&);

            virtual void report (const std::string& message, const TokenLoc& loc, Type type);
            ///< Report error to the user.

            virtual void report (const std::string& message, Type type);
            ///< Report a file related error

        public:

        // constructors

            StreamErrorHandler (std::ostream& ErrorStream);
            ///< constructor
    };
}

#endif
