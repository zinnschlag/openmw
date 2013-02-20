/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INTERPRETER_CONTROLOPCODES_H_INCLUDED
#define INTERPRETER_CONTROLOPCODES_H_INCLUDED

#include <stdexcept>

#include "opcodes.hpp"
#include "runtime.hpp"

namespace Interpreter
{
    class OpReturn : public Opcode0
    {
        public:
        
            virtual void execute (Runtime& runtime)
            {
                runtime.setPC (-1);
            }           
    };
    
    class OpSkipZero : public Opcode0
    {
        public:
        
            virtual void execute (Runtime& runtime)
            {
                Type_Integer data = runtime[0].mInteger;
                runtime.pop();
                
                if (data==0)
                    runtime.setPC (runtime.getPC()+1);
            }           
    };    
    
    class OpSkipNonZero : public Opcode0
    {
        public:
        
            virtual void execute (Runtime& runtime)
            {
                Type_Integer data = runtime[0].mInteger;
                runtime.pop();
                
                if (data!=0)
                    runtime.setPC (runtime.getPC()+1);
            }           
    };      
    
    class OpJumpForward : public Opcode1
    {
        public:
        
            virtual void execute (Runtime& runtime, unsigned int arg0)
            {
                if (arg0==0)
                    throw std::logic_error ("inifite loop");
                
                runtime.setPC (runtime.getPC()+arg0-1);
            }           
    };        

    class OpJumpBackward : public Opcode1
    {
        public:
        
            virtual void execute (Runtime& runtime, unsigned int arg0)
            {
                if (arg0==0)
                    throw std::logic_error ("inifite loop");
                
                runtime.setPC (runtime.getPC()-arg0-1);
            }           
    };        
}

#endif
