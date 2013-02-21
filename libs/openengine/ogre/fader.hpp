/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OENGINE_OGRE_FADE_H
#define OENGINE_OGRE_FADE_H

/*
  A class that handles fading in the screen from black or fading it out to black.
  
  To achieve this, it uses a full-screen Rectangle2d
 */
 
namespace Ogre
{
    class TextureUnitState;
    class Rectangle2D;
    class SceneManager;
}

namespace OEngine {
namespace Render
{
    class Fader
    {
    public:
        Fader(Ogre::SceneManager* sceneMgr);
        ~Fader();

        void update(float dt);

        void fadeIn(const float time);
        void fadeOut(const float time);
        void fadeTo(const int percent, const float time);

    private:
        enum FadingMode
        {
            FadingMode_In,
            FadingMode_Out
        };

        void applyAlpha();

        Ogre::TextureUnitState* mFadeTextureUnit;
        Ogre::Rectangle2D* mRectangle;

        FadingMode mMode;

        float mRemainingTime;
        float mTargetTime;
        float mTargetAlpha;
        float mCurrentAlpha;
        float mStartAlpha;

        Ogre::SceneManager* mSceneMgr;
    };
    }}
#endif
