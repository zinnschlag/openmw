/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "output.hpp"

#include <cassert>
#include <algorithm>
#include <iterator>

#include "locals.hpp"

namespace Compiler
{
    Output::Output (Locals& locals) : mLocals (locals) {}

    void Output::getCode (std::vector<Interpreter::Type_Code>& code) const
    {
        code.clear();
        
        // header
        code.push_back (static_cast<Interpreter::Type_Code> (mCode.size()));
        
        assert (mLiterals.getIntegerSize()%4==0);
        code.push_back (static_cast<Interpreter::Type_Code> (mLiterals.getIntegerSize()/4));
        
        assert (mLiterals.getFloatSize()%4==0);
        code.push_back (static_cast<Interpreter::Type_Code> (mLiterals.getFloatSize()/4));
        
        assert (mLiterals.getStringSize()%4==0);
        code.push_back (static_cast<Interpreter::Type_Code> (mLiterals.getStringSize()/4));
        
        // code
        std::copy (mCode.begin(), mCode.end(), std::back_inserter (code));
        
        // literals
        mLiterals.append (code);
    }

    const Literals& Output::getLiterals() const
    {
        return mLiterals;
    }
            
    const std::vector<Interpreter::Type_Code>& Output::getCode() const
    {
        return mCode;
    }
            
    const Locals& Output::getLocals() const
    {
        return mLocals;
    }

    Literals& Output::getLiterals()
    {
        return mLiterals;
    }
    
    std::vector<Interpreter::Type_Code>& Output::getCode()
    {
        return mCode;
    }
    
    Locals& Output::getLocals()
    {
        return mLocals;
    }
    
    void Output::clear()
    {
        mLiterals.clear();
        mCode.clear();
        mLocals.clear();
    }
}

