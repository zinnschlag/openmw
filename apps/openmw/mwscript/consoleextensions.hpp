/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_SCRIPT_CONSOLEEXTENSIONS_H
#define GAME_SCRIPT_CONSOLEEXTENSIONS_H

namespace Compiler
{
    class Extensions;
}

namespace Interpreter
{
    class Interpreter;
}

namespace MWScript
{
    /// \brief Script functionality limited to the console
    namespace Console
    {
        void registerExtensions (Compiler::Extensions& extensions);

        void installOpcodes (Interpreter::Interpreter& interpreter);
    }
}

#endif
