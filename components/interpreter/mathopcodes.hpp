/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INTERPRETER_MATHOPCODES_H_INCLUDED
#define INTERPRETER_MATHOPCODES_H_INCLUDED

#include <stdexcept>
#include <cmath>

#include "opcodes.hpp"
#include "runtime.hpp"

namespace Interpreter
{
    template<typename T>
    class OpAddInt : public Opcode0
    {
        public:
        
            virtual void execute (Runtime& runtime)
            {
                T result = getData<T> (runtime[1]) + getData<T> (runtime[0]);
                
                runtime.pop();
                
                getData<T> (runtime[0]) = result;
            }           
    };

    template<typename T>
    class OpSubInt : public Opcode0
    {
        public:
        
            virtual void execute (Runtime& runtime)
            {
                T result = getData<T> (runtime[1]) - getData<T> (runtime[0]);
                
                runtime.pop();

                getData<T> (runtime[0]) = result;
            }           
    };

    template<typename T>
    class OpMulInt : public Opcode0
    {
        public:
        
            virtual void execute (Runtime& runtime)
            {
                T result = getData<T> (runtime[1]) * getData<T> (runtime[0]);
                
                runtime.pop();

                getData<T> (runtime[0]) = result;
            }           
    };

    template<typename T>
    class OpDivInt : public Opcode0
    {
        public:
        
            virtual void execute (Runtime& runtime)
            {
                T left = getData<T> (runtime[0]);
            
                if (left==0)
                    throw std::runtime_error ("division by zero");
            
                T result = getData<T> (runtime[1]) / left;
                
                runtime.pop();

                getData<T> (runtime[0]) = result;
            }           
    };
    
    class OpSquareRoot : public Opcode0
    {
        public:
        
            virtual void execute (Runtime& runtime)
            {
                Type_Float value = runtime[0].mFloat;
                
                if (value<0)
                    throw std::runtime_error (
                        "square root of negative number (we aren't that imaginary)");
                
                value = std::sqrt (value);
                
                runtime[0].mFloat = value;
            }           
    };    
    
    template<typename T, typename C>
    class OpCompare : public Opcode0
    {
        public:
        
            virtual void execute (Runtime& runtime)
            {
                int result = C() (getData<T> (runtime[1]), getData<T> (runtime[0]));
                
                runtime.pop();
                
                runtime[0].mInteger = result;
            }           
    };    
}

#endif

