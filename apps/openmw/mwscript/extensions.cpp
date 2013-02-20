/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "extensions.hpp"

#include <components/interpreter/interpreter.hpp>
#include <components/interpreter/installopcodes.hpp>

#include "soundextensions.hpp"
#include "cellextensions.hpp"
#include "miscextensions.hpp"
#include "guiextensions.hpp"
#include "skyextensions.hpp"
#include "statsextensions.hpp"
#include "containerextensions.hpp"
#include "aiextensions.hpp"
#include "controlextensions.hpp"
#include "dialogueextensions.hpp"
#include "animationextensions.hpp"
#include "transformationextensions.hpp"
#include "consoleextensions.hpp"
#include "userextensions.hpp"

namespace MWScript
{
    void registerExtensions (Compiler::Extensions& extensions, bool consoleOnly)
    {
        Cell::registerExtensions (extensions);
        Misc::registerExtensions (extensions);
        Gui::registerExtensions (extensions);
        Sound::registerExtensions (extensions);
        Sky::registerExtensions (extensions);
        Stats::registerExtensions (extensions);
        Container::registerExtensions (extensions);
        Ai::registerExtensions (extensions);
        Control::registerExtensions (extensions);
        Dialogue::registerExtensions (extensions);
        Animation::registerExtensions (extensions);
        Transformation::registerExtensions (extensions);

        if (consoleOnly)
        {
            Console::registerExtensions (extensions);
            User::registerExtensions (extensions);
        }
    }

    void installOpcodes (Interpreter::Interpreter& interpreter, bool consoleOnly)
    {
        Interpreter::installOpcodes (interpreter);
        Cell::installOpcodes (interpreter);
        Misc::installOpcodes (interpreter);
        Gui::installOpcodes (interpreter);
        Sound::installOpcodes (interpreter);
        Sky::installOpcodes (interpreter);
        Stats::installOpcodes (interpreter);
        Container::installOpcodes (interpreter);
        Ai::installOpcodes (interpreter);
        Control::installOpcodes (interpreter);
        Dialogue::installOpcodes (interpreter);
        Animation::installOpcodes (interpreter);
        Transformation::installOpcodes (interpreter);

        if (consoleOnly)
        {
            Console::installOpcodes (interpreter);
            User::installOpcodes (interpreter);
        }
    }
}
