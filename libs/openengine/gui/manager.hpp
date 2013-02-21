/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OENGINE_MYGUI_MANAGER_H
#define OENGINE_MYGUI_MANAGER_H

namespace MyGUI
{
  class Gui;
  class LogManager;
  class OgreDataManager;
  class OgreRenderManager;
}

namespace Ogre
{
  class RenderWindow;
  class SceneManager;
}

namespace OEngine {
namespace GUI
{
    class MyGUIManager
    {
        MyGUI::Gui *mGui;
        MyGUI::LogManager* mLogManager;
        MyGUI::OgreDataManager* mDataManager;
        MyGUI::OgreRenderManager* mRenderManager;
        Ogre::SceneManager* mSceneMgr;


    public:
        MyGUIManager() : mLogManager(NULL), mDataManager(NULL), mRenderManager(NULL),  mGui(NULL) {}
        MyGUIManager(Ogre::RenderWindow *wnd, Ogre::SceneManager *mgr, bool logging=false, const std::string& logDir = std::string(""))
        {
            setup(wnd,mgr,logging, logDir);
        }
        ~MyGUIManager()
        {
            shutdown();
        }

        void setup(Ogre::RenderWindow *wnd, Ogre::SceneManager *mgr, bool logging=false, const std::string& logDir = std::string(""));
        void shutdown();

        MyGUI::Gui *getGui() { return mGui; }
    };
}
}
#endif
