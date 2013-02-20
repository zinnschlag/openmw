/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COMPILER_LOCALS_H_INCLUDED
#define COMPILER_LOCALS_H_INCLUDED

#include <vector>
#include <string>
#include <iosfwd>

namespace Compiler
{
    /// \brief Local variable declarations
    
    class Locals
    {
            std::vector<std::string> mShorts;
            std::vector<std::string> mLongs;
            std::vector<std::string> mFloats;
    
            const std::vector<std::string>& get (char type) const;

            int searchIndex (char type, const std::string& name) const;

            bool search (char type, const std::string& name) const;
            
            std::vector<std::string>& get (char type);   
    
        public:
    
            char getType (const std::string& name) const;
            ///< 's': short, 'l': long, 'f': float, ' ': does not exist.
            
            int getIndex (const std::string& name) const;
            ///< return index for local variable \a name (-1: does not exist).
            
            void write (std::ostream& localFile) const;
            ///< write declarations to file.
            
            void declare (char type, const std::string& name);
            ///< declares a variable.
            
            void clear();
            ///< remove all declarations.
    };
}

#endif
