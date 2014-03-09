#ifndef GAME_SHADOWS_H
#define GAME_SHADOWS_H

#include <OgreShadowCameraSetupPSSM.h>
#define STABLEPSSM 

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
    class StablePSSMShadowCameraSetup: public Ogre::PSSMShadowCameraSetup
    {
    public:
		/// Constructor, defaults to 3 splits
		StablePSSMShadowCameraSetup();
		~StablePSSMShadowCameraSetup();

        /// Returns a shadow camera with PSSM splits base on iteration with rotation/translation-invariant size.
		virtual void getShadowCamera(const Ogre::SceneManager *sm, const Ogre::Camera *cam,
			const Ogre::Viewport *vp, const Ogre::Light *light, Ogre::Camera *texCam, size_t iteration) const;
    };

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

#ifdef STABLEPSSM
        StablePSSMShadowCameraSetup* mPSSMSetup;
#else
        Ogre::PSSMShadowCameraSetup* mPSSMSetup;
#endif
        
        float mShadowFar;
        float mFadeStart;
    };
}

#endif
