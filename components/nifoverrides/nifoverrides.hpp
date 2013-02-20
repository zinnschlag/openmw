/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COMPONENTS_NIFOVERRIDES_H
#define COMPONENTS_NIFOVERRIDES_H

#include <OgreConfigFile.h>

namespace NifOverrides
{

    typedef std::pair<bool, int> TransparencyResult;

    /// \brief provide overrides for some model / texture properties that bethesda has chosen poorly
    class Overrides
    {
    public:
        static Ogre::ConfigFile mTransparencyOverrides;
        void loadTransparencyOverrides (const std::string& file);

        static TransparencyResult getTransparencyOverride(const std::string& texture);
    };

}

#endif
