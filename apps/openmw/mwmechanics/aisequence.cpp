/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "aisequence.hpp"

#include "aipackage.hpp"

void MWMechanics::AiSequence::copy (const AiSequence& sequence)
{
    for (std::list<AiPackage *>::const_iterator iter (sequence.mPackages.begin());
        iter!=sequence.mPackages.end(); ++iter)
        mPackages.push_back ((*iter)->clone());
}

MWMechanics::AiSequence::AiSequence() : mDone (false) {}

MWMechanics::AiSequence::AiSequence (const AiSequence& sequence) : mDone (false)
{
    copy (sequence);
}

MWMechanics::AiSequence& MWMechanics::AiSequence::operator= (const AiSequence& sequence)
{
    if (this!=&sequence)
    {
        clear();
        copy (sequence);
    }
    
    return *this;
}

MWMechanics::AiSequence::~AiSequence()
{
    clear();
}

int MWMechanics::AiSequence::getTypeId() const
{
    if (mPackages.empty())
        return -1;
        
    return mPackages.front()->getTypeId();
}

bool MWMechanics::AiSequence::isPackageDone() const
{
    return mDone;
}

void MWMechanics::AiSequence::execute (const MWWorld::Ptr& actor)
{
    if (!mPackages.empty())
    {
        if (mPackages.front()->execute (actor))
        {
            mPackages.erase (mPackages.begin());
            mDone = true;
        }
        else
            mDone = false;    
    }
}

void MWMechanics::AiSequence::clear()
{
    for (std::list<AiPackage *>::const_iterator iter (mPackages.begin()); iter!=mPackages.end(); ++iter)
        delete *iter;

    mPackages.clear();
}

void MWMechanics::AiSequence::stack (const AiPackage& package)
{
    mPackages.push_front (package.clone());
}

void MWMechanics::AiSequence::queue (const AiPackage& package)
{
    mPackages.push_back (package.clone());
}
