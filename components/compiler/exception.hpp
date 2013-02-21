/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COMPILER_EXCEPTION_H_INCLUDED
#define COMPILER_EXCEPTION_H_INCLUDED

#include <exception>

namespace Compiler
{
    /// \brief Exception: Error while parsing the source

    class SourceException : public std::exception
    {
        public:
        
            virtual const char *what() const throw() { return "compile error";} 
            ///< Return error message
    };

    /// \brief Exception: File error

    class FileException : public SourceException
    {
        public:
        
            virtual const char *what() const throw() { return "can't read file"; }
            ///< Return error message
    };

    /// \brief Exception: EOF condition encountered

    class EOFException : public SourceException
    {       
        public:
        
            virtual const char *what() const throw() { return "end of file"; }
            ///< Return error message
    };
}

#endif
