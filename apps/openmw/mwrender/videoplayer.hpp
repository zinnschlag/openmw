/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <OgreMaterial.h>

namespace Ogre
{
    class SceneManager;
    class SceneNode;
    class Rectangle2D;
}

namespace MWRender
{
    struct VideoState;

    class VideoPlayer
    {
    public:
        VideoPlayer(Ogre::SceneManager* sceneMgr);
        ~VideoPlayer();

        void playVideo (const std::string& resourceName, bool allowSkipping);

        void update();

        void close();
        void stopVideo();

        bool isPlaying();

        void setResolution (int w, int h) { mWidth = w; mHeight = h; }


    private:
        VideoState* mState;

        bool mAllowSkipping;

        Ogre::SceneManager* mSceneMgr;
        Ogre::MaterialPtr mVideoMaterial;
        Ogre::Rectangle2D* mRectangle;
        Ogre::Rectangle2D* mBackgroundRectangle;
        Ogre::SceneNode* mNode;
        Ogre::SceneNode* mBackgroundNode;

        int mWidth;
        int mHeight;
    };
}

#endif
