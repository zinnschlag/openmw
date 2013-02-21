/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INTERPRETER_DEFINES_H_INCLUDED
#define INTERPRETER_DEFINES_H_INCLUDED

#include <string>
#include "context.hpp"

namespace Interpreter{
    std::string fixDefinesDialog(std::string text, Context& context);
    std::string fixDefinesMsgBox(std::string text, Context& context);
    std::string fixDefinesBook(std::string text, Context& context);
}

#endif
