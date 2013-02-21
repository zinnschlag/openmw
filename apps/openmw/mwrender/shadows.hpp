/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_SHADOWS_H
#define GAME_SHADOWS_H

// forward declares
namespace Ogre
{
    class SceneManager;
    class PSSMShadowCameraSetup;
}
namespace OEngine{
    namespace Render{
        class OgreRenderer;
    }
}

namespace MWRender
{
    class Shadows
    {
    public:
        Shadows(OEngine::Render::OgreRenderer* rend);

        void recreate();

        Ogre::PSSMShadowCameraSetup* getPSSMSetup();
        float getShadowFar() const;
        float getFadeStart() const;

    protected:
        OEngine::Render::OgreRenderer* mRendering;
        Ogre::SceneManager* mSceneMgr;

        Ogre::PSSMShadowCameraSetup* mPSSMSetup;
        float mShadowFar;
        float mFadeStart;
    };
}

#endif
