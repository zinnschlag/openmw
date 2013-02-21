/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWSCRIPT_REF_H
#define GAME_MWSCRIPT_REF_H

#include <string>

#include <components/interpreter/runtime.hpp>

#include "../mwbase/environment.hpp"
#include "../mwbase/world.hpp"

#include "../mwworld/ptr.hpp"

#include "interpretercontext.hpp"

namespace MWScript
{
    struct ExplicitRef
    {
        MWWorld::Ptr operator() (Interpreter::Runtime& runtime) const
        {
            std::string id = runtime.getStringLiteral (runtime[0].mInteger);
            runtime.pop();

            return MWBase::Environment::get().getWorld()->getPtr (id, false);
        }
    };

    struct ImplicitRef
    {
        MWWorld::Ptr operator() (Interpreter::Runtime& runtime) const
        {
            MWScript::InterpreterContext& context
                = static_cast<MWScript::InterpreterContext&> (runtime.getContext());

            return context.getReference();
        }
    };
}

#endif
