/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INTERPRETER_RUNTIME_H_INCLUDED
#define INTERPRETER_RUNTIME_H_INCLUDED

#include <vector>
#include <string>

#include "types.hpp"

namespace Interpreter
{
    class Context;

    /// Runtime data and engine interface

    class Runtime
    {
            Context *mContext;
            const Type_Code *mCode;
            int mCodeSize;
            int mPC;
            std::vector<Data> mStack;

        public:

            Runtime ();

            int getPC() const;
            ///< return program counter.

            int getIntegerLiteral (int index) const;

            float getFloatLiteral (int index) const;

            std::string getStringLiteral (int index) const;

            void configure (const Type_Code *code, int codeSize, Context& context);
            ///< \a context and \a code must exist as least until either configure, clear or
            /// the destructor is called. \a codeSize is given in 32-bit words.

            void clear();

            void setPC (int PC);
            ///< set program counter.

            void push (const Data& data);
            ///< push data on stack

            void push (Type_Integer value);
            ///< push integer data on stack.

            void push (Type_Float value);
            ///< push float data on stack.

            void pop();
            ///< pop stack

            Data& operator[] (int Index);
            ///< Access stack member, counted from the top.

            Context& getContext();
    };
}

#endif
