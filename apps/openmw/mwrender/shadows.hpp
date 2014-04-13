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
    class StablePSSMShadowCameraSetup: public Ogre::DefaultShadowCameraSetup
    {
    public:
		/// Constructor, defaults to 3 splits
		StablePSSMShadowCameraSetup();
		~StablePSSMShadowCameraSetup();

        /** Calculate a new splitting scheme.
        @param cascadeCount The number of cascades to use
        @param firstSplitDist distance of the first split
        @param farDist The far plane to use for the last split
        @param lambda Value between 0 (linear splits) and 1 (logarithmic splits)
        */
        void calculateSplitPoints(size_t cascadeCount, Ogre::Real firstSplitDist, Ogre::Real farDist, Ogre::Real lambda = 0.95);

        /** Manually configure a new splitting scheme.
        @param newSplitPoints A list which is cascadeCount + 1 entries long, containing the
	        split points. The first value is the near point, the last value is the
	        far point, and each value in between is both a far point of the previous
	        split, and a near point for the next one.
        */
        void setSplitPoints(const Ogre::PSSMShadowCameraSetup::SplitPointList& newSplitPoints);

        /// Get the number of splits. 
	    size_t getCascadeCount() const { return mCascadeCount; }

        /// Returns the calculated split points.
	    inline const Ogre::PSSMShadowCameraSetup::SplitPointList& getSplitPoints() const
	    { return mSplitPoints; }

        /// Returns a shadow camera with PSSM splits base on iteration with rotation/translation-invariant size.
		virtual void getShadowCamera(const Ogre::SceneManager *sm, const Ogre::Camera *cam,
			const Ogre::Viewport *vp, const Ogre::Light *light, Ogre::Camera *texCam, size_t iteration) const;

    private:
	    size_t mCascadeCount;
	    Ogre::PSSMShadowCameraSetup::SplitPointList mSplitPoints;

	    mutable size_t mCurrentIteration;
    };

    class Shadows
    {
    public:
        Shadows(OEngine::Render::OgreRenderer* rend);

        void recreate();

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
