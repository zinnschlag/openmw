/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_SCRIPT_COMPILERCONTEXT_H
#define GAME_SCRIPT_COMPILERCONTEXT_H

#include <components/compiler/context.hpp>

namespace MWScript
{
    class CompilerContext : public Compiler::Context
    {
        public:

            enum Type
            {
                Type_Full, // global, local, targetted
                Type_Dialgoue,
                Type_Console
            };

        private:

            Type mType;

        public:

            CompilerContext (Type type);

            /// Is the compiler allowed to declare local variables?
            virtual bool canDeclareLocals() const;

            /// 'l: long, 's': short, 'f': float, ' ': does not exist.
            virtual char getGlobalType (const std::string& name) const;

            virtual char getMemberType (const std::string& name, const std::string& id) const;
            ///< 'l: long, 's': short, 'f': float, ' ': does not exist.

            virtual bool isId (const std::string& name) const;
            ///< Does \a name match an ID, that can be referenced?
    };
}

#endif
