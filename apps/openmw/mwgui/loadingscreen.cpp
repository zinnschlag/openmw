#include "loadingscreen.hpp"

#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreCompositorManager.h>
#include <OgreCompositorChain.h>
#include <OgreMaterial.h>



#include "../mwbase/environment.hpp"
#include "../mwbase/inputmanager.hpp"

namespace MWGui
{

    LoadingScreen::LoadingScreen(Ogre::SceneManager* sceneMgr, Ogre::RenderWindow* rw, MWBase::WindowManager& parWindowManager)
        : mSceneMgr(sceneMgr)
        , mWindow(rw)
        , WindowBase("openmw_loading_screen.layout", parWindowManager)
        , mLoadingOn(false)
        , mLastRenderTime(0.f)
    {
        getWidget(mLoadingText, "LoadingText");
        getWidget(mProgressBar, "ProgressBar");
        getWidget(mBackgroundImage, "BackgroundImage");


        mBackgroundMaterial = Ogre::MaterialManager::getSingleton().create("BackgroundMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        mBackgroundMaterial->getTechnique(0)->getPass(0)->setLightingEnabled(false);
        mBackgroundMaterial->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
        mBackgroundMaterial->getTechnique(0)->getPass(0)->createTextureUnitState("");

        mRectangle = new Ogre::Rectangle2D(true);
        mRectangle->setCorners(-1.0, 1.0, 1.0, -1.0);
        mRectangle->setMaterial("BackgroundMaterial");
        // Render the background before everything else
        mRectangle->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY-1);
        // Use infinite AAB to always stay visible
        Ogre::AxisAlignedBox aabInf;
        aabInf.setInfinite();
        mRectangle->setBoundingBox(aabInf);
        // Attach background to the scene
        Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
        node->attachObject(mRectangle);
        mRectangle->setVisible(false);
    }

    LoadingScreen::~LoadingScreen()
    {
        delete mRectangle;
    }

    void LoadingScreen::onResChange(int w, int h)
    {
        setCoord(0,0,w,h);
    }

    void LoadingScreen::setLoadingProgress (const std::string& stage, int depth, int current, int total)
    {
        if (!mLoadingOn)
            loadingOn();

        const int numRefLists = 20;

        if (depth == 0)
        {
            mCurrentCellLoading = current;
            mTotalCellsLoading = total;

            mCurrentRefLoading = 0;
            mCurrentRefList = 0;
        }
        else if (depth == 1)
        {
            mCurrentRefLoading = current;
            mTotalRefsLoading = total;
        }

        if (mTotalCellsLoading == 0)
        {
            loadingOff();
            return;
        }

        float refProgress;
        if (mTotalRefsLoading <= 1)
            refProgress = 1;
        else
            refProgress = float(mCurrentRefLoading) / float(mTotalRefsLoading-1);
        refProgress += mCurrentRefList;
        refProgress /= numRefLists;

        assert(refProgress <= 1 && refProgress >= 0);

        if (depth == 1 && mCurrentRefLoading == mTotalRefsLoading-1)
            ++mCurrentRefList;

        float progress = (float(mCurrentCellLoading)+refProgress) / float(mTotalCellsLoading);
        assert(progress <= 1 && progress >= 0);
        if (progress >= 1)
        {
            loadingOff();
            return;
        }

        mLoadingText->setCaption(stage + "... ");
        mProgressBar->setProgressPosition (static_cast<size_t>(progress * 1000));

        static float loadingScreenFps = 30.f;

        if (mTimer.getMilliseconds () > mLastRenderTime + (1.f/loadingScreenFps) * 1000.f)
        {
            mLastRenderTime = mTimer.getMilliseconds ();


            // Turn off rendering except the GUI
            mSceneMgr->clearSpecialCaseRenderQueues();
            // SCRQM_INCLUDE with RENDER_QUEUE_OVERLAY does not work.
            for (int i = 0; i < Ogre::RENDER_QUEUE_MAX; ++i)
            {
                if (i > 0 && i < 96)
                    mSceneMgr->addSpecialCaseRenderQueue(i);
            }
            mSceneMgr->setSpecialCaseRenderQueueMode(Ogre::SceneManager::SCRQM_EXCLUDE);

            // always update input before rendering something, otherwise mygui goes crazy when something was entered in the frame before
            // (e.g. when using "coc" console command, it would enter an infinite loop and crash due to overflow)
            MWBase::Environment::get().getInputManager()->update(0, true);

            Ogre::CompositorChain* chain = Ogre::CompositorManager::getSingleton().getCompositorChain(mWindow->getViewport(0));

            bool hasCompositor = chain->getCompositor ("gbufferFinalizer");


            if (!hasCompositor)
            {
                mWindow->getViewport(0)->setClearEveryFrame(false);
            }
            else
            {
                mBackgroundMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(chain->getCompositor ("gbufferFinalizer")->getTextureInstance ("no_mrt_output", 0)->getName());
                mRectangle->setVisible(true);

                for (unsigned int i = 0; i<chain->getNumCompositors(); ++i)
                {
                    Ogre::CompositorManager::getSingleton().setCompositorEnabled(mWindow->getViewport(0), chain->getCompositor(i)->getCompositor()->getName(), false);
                }
            }

            mWindow->update();

            if (!hasCompositor)
                mWindow->getViewport(0)->setClearEveryFrame(true);
            else
            {
                for (unsigned int i = 0; i<chain->getNumCompositors(); ++i)
                {
                    Ogre::CompositorManager::getSingleton().setCompositorEnabled(mWindow->getViewport(0), chain->getCompositor(i)->getCompositor()->getName(), true);
                }
                mRectangle->setVisible(false);
            }

            // resume 3d rendering
            mSceneMgr->clearSpecialCaseRenderQueues();
            mSceneMgr->setSpecialCaseRenderQueueMode(Ogre::SceneManager::SCRQM_EXCLUDE);
        }
    }

    void LoadingScreen::loadingOn()
    {
        setVisible(true);
        mLoadingOn = true;
    }


    void LoadingScreen::loadingOff()
    {
        setVisible(false);
        mLoadingOn = false;
    }
}
