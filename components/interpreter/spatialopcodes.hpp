/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INTERPRETER_SPATIALOPCODES_H_INCLUDED
#define INTERPRETER_SPATIALOPCODES_H_INCLUDED

#include "opcodes.hpp"
#include "runtime.hpp"

namespace Interpreter
{    
    class OpGetDistance : public Opcode0
    {
        public:
        
            virtual void execute (Runtime& runtime)
            {
                std::string name = runtime.getStringLiteral (runtime[0].mInteger);            
                
                Type_Float distance = runtime.getContext().getDistance (name);
                
                runtime[0].mFloat = distance;
            }            
    };
    
    class OpGetDistanceExplicit : public Opcode0
    {
        public:
        
            virtual void execute (Runtime& runtime)
            {
                int index = runtime[0].mInteger;
                runtime.pop();
                std::string id = runtime.getStringLiteral (index);
                            
                std::string name = runtime.getStringLiteral (runtime[0].mInteger);
                
                Type_Float distance = runtime.getContext().getDistance (name, id);
                
                runtime[0].mFloat = distance;
            }            
    };    
}

#endif

