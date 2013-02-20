/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INTERPRETER_SCRIPTOPCODES_H_INCLUDED
#define INTERPRETER_SCRIPTOPCODES_H_INCLUDED

#include "opcodes.hpp"
#include "runtime.hpp"
#include "context.hpp"

namespace Interpreter
{
    class OpScriptRunning : public Opcode0
    {
        public:
        
            virtual void execute (Runtime& runtime)
            {
                std::string name = runtime.getStringLiteral (runtime[0].mInteger);
                runtime[0].mInteger = runtime.getContext().isScriptRunning (name);
            }           
    };

    class OpStartScript : public Opcode0
    {
        public:
        
            virtual void execute (Runtime& runtime)
            {
                std::string name = runtime.getStringLiteral (runtime[0].mInteger);
                runtime.pop();
                runtime.getContext().startScript (name);
            }           
    };

    class OpStopScript : public Opcode0
    {
        public:
        
            virtual void execute (Runtime& runtime)
            {
                std::string name = runtime.getStringLiteral (runtime[0].mInteger);
                runtime.pop();
                runtime.getContext().stopScript (name);
            }           
    };
}

#endif

