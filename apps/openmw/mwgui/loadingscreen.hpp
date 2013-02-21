/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_LOADINGSCREEN_H
#define MWGUI_LOADINGSCREEN_H

#include <OgreSceneManager.h>
#include <OgreResourceGroupManager.h>

#include "window_base.hpp"

namespace MWGui
{
    class LoadingScreen : public WindowBase
    {
    public:
        LoadingScreen(Ogre::SceneManager* sceneMgr, Ogre::RenderWindow* rw, MWBase::WindowManager& parWindowManager);
        virtual ~LoadingScreen();

        void setLoadingProgress (const std::string& stage, int depth, int current, int total);
        void loadingDone();

        void onResChange(int w, int h);

    private:
        bool mFirstLoad;

        Ogre::SceneManager* mSceneMgr;
        Ogre::RenderWindow* mWindow;

        unsigned long mLastWallpaperChangeTime;
        unsigned long mLastRenderTime;
        Ogre::Timer mTimer;

        MyGUI::TextBox* mLoadingText;
        MyGUI::ProgressBar* mProgressBar;
        MyGUI::ImageBox* mBackgroundImage;

        int mCurrentCellLoading;
        int mTotalCellsLoading;
        int mCurrentRefLoading;
        int mTotalRefsLoading;
        int mCurrentRefList;

        Ogre::Rectangle2D* mRectangle;
        Ogre::MaterialPtr mBackgroundMaterial;

        Ogre::StringVectorPtr mResources;

        bool mLoadingOn;

        void loadingOn();
        void loadingOff();

        void changeWallpaper();
    };

}


#endif
