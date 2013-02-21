/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "nifoverrides.hpp"

#include <OgreStringConverter.h>

#include <../components/misc/stringops.hpp>


using namespace NifOverrides;

Ogre::ConfigFile Overrides::mTransparencyOverrides = Ogre::ConfigFile();

void Overrides::loadTransparencyOverrides (const std::string& file)
{
    mTransparencyOverrides.load(file);
}

TransparencyResult Overrides::getTransparencyOverride(const std::string& texture)
{
    TransparencyResult result;
    result.first = false;

    std::string tex = texture;
    Misc::StringUtils::toLower(tex);

    Ogre::ConfigFile::SectionIterator seci = mTransparencyOverrides.getSectionIterator();
    while (seci.hasMoreElements())
    {
        Ogre::String sectionName = seci.peekNextKey();
        if (sectionName == tex)
        {
            result.first = true;
            result.second = Ogre::StringConverter::parseInt(mTransparencyOverrides.getSetting("alphaRejectValue", sectionName));
            break;
        }
        seci.getNext();
    }
    return result;
}
