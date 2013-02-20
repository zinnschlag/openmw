/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_RENDERING_EXTERNALRENDERING_H
#define GAME_RENDERING_EXTERNALRENDERING_H

namespace Ogre
{
    class SceneManager;
}

namespace MWRender
{
    /// \brief Base class for out of world rendering
    class ExternalRendering
    {
        public:
        
            virtual void setup (Ogre::SceneManager *sceneManager) = 0;
        
            virtual ~ExternalRendering() {}
    };
}

#endif

