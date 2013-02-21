/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>
#include <cassert>

#include "manager.hpp"

using namespace OEngine::GUI;

/*
 *  As of MyGUI 3.2.0, MyGUI::OgreDataManager::isDataExist is unnecessarily complex
 *  this override fixes the resulting performance issue.
 */
class FixedOgreDataManager : public MyGUI::OgreDataManager
{
public:
    bool isDataExist(const std::string& _name)
    {
        return Ogre::ResourceGroupManager::getSingleton().resourceExistsInAnyGroup (_name);
    }
};

void MyGUIManager::setup(Ogre::RenderWindow *wnd, Ogre::SceneManager *mgr, bool logging, const std::string& logDir)
{
    assert(wnd);
    assert(mgr);

    mSceneMgr = mgr;

    using namespace MyGUI;

    // Enable/disable MyGUI logging to stdout. (Logging to MyGUI.log is
    // still enabled.) In order to do this we have to initialize the log
    // manager before the main gui system itself, otherwise the main
    // object will get the chance to spit out a few messages before we
    // can able to disable it.

    std::string theLogFile = std::string(MYGUI_PLATFORM_LOG_FILENAME);
    if(!logDir.empty())
        theLogFile.insert(0, logDir);

    // Set up OGRE platform (bypassing OgrePlatform). We might make this more generic later.
    mLogManager = new LogManager();
    mRenderManager = new OgreRenderManager();
    mDataManager = new FixedOgreDataManager();

    LogManager::getInstance().setSTDOutputEnabled(logging);

    if (!theLogFile.empty())
        LogManager::getInstance().createDefaultSource(theLogFile);

    mRenderManager->initialise(wnd, mgr);
    mDataManager->initialise("General");

    // Create GUI
    mGui = new Gui();
    mGui->initialise("core.xml");
}

void MyGUIManager::shutdown()
{
    mGui->shutdown ();
    delete mGui;
    if(mRenderManager)
    {
        mRenderManager->shutdown();
        delete mRenderManager;
        mRenderManager = NULL;
    }
    if(mDataManager)
    {
        mDataManager->shutdown();
        delete mDataManager;
        mDataManager = NULL;
    }
    if (mLogManager)
    {
        delete mLogManager;
        mLogManager = NULL;
    }
    mGui = NULL;
}
