#include "shadows.hpp"

#include <components/settings/settings.hpp>
#include <openengine/ogre/renderer.hpp>

#include <OgreSceneManager.h>
#include <OgreColourValue.h>
#include <OgreShadowCameraSetupLiSPSM.h>
#include <OgreShadowCameraSetupPSSM.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreCamera.h>
#include <OgreRenderTexture.h>
#include <OgreViewport.h>

#include <extern/shiny/Main/Factory.hpp>

#include "renderconst.hpp"

using namespace Ogre;
using namespace MWRender;

Ogre::Vector3* GetFrustumSlicePoints(const Ogre::Camera *cam, Ogre::Real z, bool InWorldSpace = false)
{
    Ogre::Vector3 *points = new Ogre::Vector3[4];

    float halfH = z * Ogre::Math::Tan(cam->getFOVy()/2);
    float halfW = halfH * cam->getAspectRatio();
    Ogre::Vector3 vUp, vRight, vFwd, vPos;
    if(InWorldSpace)
    {
        vUp = cam->getDerivedUp();
        vRight = cam->getDerivedRight();
        vFwd = cam->getDerivedDirection();
        vPos = cam->getDerivedPosition();
        vUp.normalise();
        vRight.normalise();
        vFwd.normalise();
    }
    else
    {
        vUp = Vector3::UNIT_Y;
        vRight = Vector3::UNIT_X;
        vFwd = Vector3::UNIT_Z;
        vPos = Vector3::ZERO;
    }
    
    points[0] = vPos + vFwd*z - vRight*halfW + vUp*halfH; // left top
    points[1] = vPos + vFwd*z - vRight*halfW - vUp*halfH; // left bottom
    points[2] = vPos + vFwd*z + vRight*halfW - vUp*halfH; // right bottom
    points[3] = vPos + vFwd*z + vRight*halfW + vUp*halfH; // right top

    return points;
}

Ogre::Vector2 CalcFrustumDiagAndCenterOffset(const Ogre::Camera *cam, Ogre::Real zNear, Ogre::Real zFar)
{
    Ogre::Real tanBy2 = Ogre::Math::Tan(cam->getFOVy()/2);
    float halfH = zFar * tanBy2;
    float halfW = halfH * cam->getAspectRatio();

    // find longest diagonal length
    Vector3 points[2];
    points[0] = zFar*Vector3::UNIT_Z - halfW*Vector3::UNIT_X - halfH*Vector3::UNIT_Y;
    points[1] = zFar*Vector3::UNIT_Z + halfW*Vector3::UNIT_X + halfH*Vector3::UNIT_Y;

    Ogre::Vector2 vDiagCenterOffset;

    vDiagCenterOffset.x = (points[1]-points[0]).length(); // far left bottom - far right top

    halfH = zNear * tanBy2;
    halfW = halfH * cam->getAspectRatio();
    points[1] = zNear*Vector3::UNIT_Z + halfW*Vector3::UNIT_X + halfH*Vector3::UNIT_Y;

    vDiagCenterOffset.y = (points[1]-points[0]).length(); // from near left bottom - far right top

    if(vDiagCenterOffset.y > vDiagCenterOffset.x) vDiagCenterOffset.x = vDiagCenterOffset.y;

    // find offset to the center of frustum (for the case of max diagonal)
    Real newDiag = 0.25f * vDiagCenterOffset.x*vDiagCenterOffset.x - halfH*halfH - halfW*halfW;
    if(newDiag <= 0.0) newDiag = 0;
    else newDiag = Ogre::Math::Sqrt(newDiag);
    vDiagCenterOffset.y = zNear + newDiag;
    
    return vDiagCenterOffset;
}

StablePSSMShadowCameraSetup::StablePSSMShadowCameraSetup() : Ogre::PSSMShadowCameraSetup()
{
}

StablePSSMShadowCameraSetup::~StablePSSMShadowCameraSetup()
{
}

void StablePSSMShadowCameraSetup::getShadowCamera(const Ogre::SceneManager *sm, const Ogre::Camera *cam,
			const Ogre::Viewport *vp, const Ogre::Light *light, Ogre::Camera *texCam, size_t iteration) const
{
    // apply the right clip distance.
	Real nearDist = mSplitPoints[iteration];
	Real farDist  = mSplitPoints[iteration + 1];

	mCurrentIteration = iteration;
    
    if (light->getType() == Light::LT_DIRECTIONAL)
	{
        // get maximum needed cascade size and shadow camera offset along camera dir
        Vector2 vDiagCenter = CalcFrustumDiagAndCenterOffset(cam, nearDist, farDist);

        Vector3 pos = cam->getDerivedPosition() + cam->getDerivedDirection() * vDiagCenter.y;
    
        Vector3 dir = -light->getDerivedDirection();
	    dir.normalise();

	    Vector3 up = Vector3::UNIT_Y;
	    // Check it's not coincident with dir
	    if (Math::Abs(up.dotProduct(dir)) >= 1.0f)
	    {
	        // Use camera up
	        up = Vector3::UNIT_Z;
	    }
	    // cross twice to rederive, only direction is unaltered
	    Vector3 left = dir.crossProduct(up);
	    left.normalise();
	    up = dir.crossProduct(left);
	    up.normalise();

        Matrix4 matToLS = buildViewMatrix(pos, dir, up);

        // Get max needed z for current cascade
        Vector3 *pointsNear = GetFrustumSlicePoints(cam, nearDist, true);
        Vector3 *pointsFar = GetFrustumSlicePoints(cam, farDist, true);
        Vector3 *points = pointsNear;

        Real maxZ = -FLT_MAX;
        for(int k=0; k<2; k++)
        {
            for(int i=0; i<4; i++)
            {
                Vector3 v3 = matToLS * points[i];
                if(v3.z > maxZ) maxZ = v3.z;
            }
            points = pointsFar;
        }

        delete[] pointsNear;
        delete[] pointsFar;

        // Prepare shadow camera
        texCam->setCustomViewMatrix(false);
	    texCam->setCustomProjectionMatrix(false);

        Real nearClip = light->getShadowNearClipDistance();
		if (nearClip <= 0.0f) nearClip = cam->getNearClipDistance();

        Real shadowFar = light->getShadowFarDistance();

        texCam->setProjectionType(PT_ORTHOGRAPHIC);

        texCam->setNearClipDistance(nearClip);
        texCam->setFarClipDistance(shadowFar);

        // filter padding should be added to avoid seams between cascades
        // should be done after all diagonal calculations
        int filterPadding = 2; // value in pixels
        vDiagCenter.x *= static_cast<Ogre::Real>(texCam->getViewport()->getActualWidth() + filterPadding*2) / texCam->getViewport()->getActualWidth();
        
        texCam->setAspectRatio(1.0f);
        texCam->setOrthoWindowWidth(vDiagCenter.x);

        // Reduce jittering caused by the projection moving with the camera
	    Real worldTexelSize = (texCam->getOrthoWindowWidth()) / texCam->getViewport()->getActualWidth();
        
        pos += dir * (shadowFar - maxZ);
        Quaternion q;
        q.FromAxes(left, up, dir);
	    Vector3 lightSpacePos = q.Inverse() * pos;
		
	    //snap to nearest texel
	    lightSpacePos.x -= fmod(lightSpacePos.x, worldTexelSize);
        lightSpacePos.y -= fmod(lightSpacePos.y, worldTexelSize);

	    //convert back to world space
        pos = q * lightSpacePos;

        texCam->setPosition(pos);
        texCam->setOrientation(q);
    }
}

Shadows::Shadows(OEngine::Render::OgreRenderer* rend) :
    mShadowFar(1000), mFadeStart(0.9)
{
    mRendering = rend;
    mSceneMgr = mRendering->getScene();
    recreate();
}

void Shadows::recreate()
{
    bool enabled = Settings::Manager::getBool("enabled", "Shadows");

    bool split = Settings::Manager::getBool("split", "Shadows");
    int splitsCount = Settings::Manager::getInt("outdoor splits count", "Shadows");

    sh::Factory::getInstance ().setGlobalSetting ("shadows", enabled && !split ? "true" : "false");
    sh::Factory::getInstance ().setGlobalSetting ("shadows_pssm", enabled && split ? "true" : "false");

    if (!enabled)
    {
        mSceneMgr->setShadowTechnique(SHADOWTYPE_NONE);
        return;
    }

    int texsize = Settings::Manager::getInt("texture size", "Shadows");
    mSceneMgr->setShadowTextureSize(texsize);

    mSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED);

    // no point light shadows, i'm afraid. might revisit this with Deferred Shading
    mSceneMgr->setShadowTextureCountPerLightType(Light::LT_POINT, 0);

    mSceneMgr->setShadowTextureCountPerLightType(Light::LT_DIRECTIONAL, splitsCount);
    mSceneMgr->setShadowTextureCount(splitsCount);

    mSceneMgr->setShadowTextureSelfShadow(true);
    mSceneMgr->setShadowCasterRenderBackFaces(true);
    mSceneMgr->setShadowTextureCasterMaterial("openmw_shadowcaster_default");
    mSceneMgr->setShadowTexturePixelFormat(PF_FLOAT32_R);
    mSceneMgr->setShadowDirectionalLightExtrusionDistance(1000000);

    mShadowFar = split ? Settings::Manager::getInt("split shadow distance", "Shadows") : Settings::Manager::getInt("shadow distance", "Shadows");
    mSceneMgr->setShadowFarDistance(mShadowFar);

    mFadeStart = Settings::Manager::getFloat("fade start", "Shadows");

    ShadowCameraSetupPtr shadowCameraSetup;
    if (split)
    {
#ifdef STABLEPSSM
        mPSSMSetup = new StablePSSMShadowCameraSetup();
#else
        mPSSMSetup = new PSSMShadowCameraSetup();
#endif

        // Make sure to keep this in sync with the camera's near clip distance!
        mPSSMSetup->setSplitPadding(mRendering->getCamera()->getNearClipDistance());

        mPSSMSetup->calculateSplitPoints(splitsCount, mRendering->getCamera()->getNearClipDistance(), Settings::Manager::getFloat("max viewing distance", "Viewing distance"), 0.65);

        //const Real adjustFactors[PSSM_SPLITS] = {64, 64, 64};
        for (int i=0; i < splitsCount; ++i)
        {
            mPSSMSetup->setOptimalAdjustFactor(i, 64);
            /*if (i==0)
                mSceneMgr->setShadowTextureConfig(i, texsize, texsize, Ogre::PF_FLOAT32_R);
            else if (i ==1)
                mSceneMgr->setShadowTextureConfig(i, texsize/2, texsize/2, Ogre::PF_FLOAT32_R);
            else if (i ==2)
                mSceneMgr->setShadowTextureConfig(i, texsize/4, texsize/4, Ogre::PF_FLOAT32_R);*/
        }

        // Populate from split point 1, not 0, since split 0 isn't useful (usually 0)
        const PSSMShadowCameraSetup::SplitPointList& splitPointList = getPSSMSetup()->getSplitPoints();
        sh::Vector3* splitPoints = new sh::Vector3(splitPointList[1], splitPointList[2], splitPointList[3]);

        sh::Factory::getInstance ().setSharedParameter ("pssmSplitPoints", sh::makeProperty<sh::Vector3>(splitPoints));

        shadowCameraSetup = ShadowCameraSetupPtr(mPSSMSetup);
    }
    else
    {
        LiSPSMShadowCameraSetup* lispsmSetup = new LiSPSMShadowCameraSetup();
        lispsmSetup->setOptimalAdjustFactor(64);
        //lispsmSetup->setCameraLightDirectionThreshold(Degree(0));
        //lispsmSetup->setUseAggressiveFocusRegion(false);
        shadowCameraSetup = ShadowCameraSetupPtr(lispsmSetup);
    }
    mSceneMgr->setShadowCameraSetup(shadowCameraSetup);

    sh::Vector4* shadowFar_fadeStart = new sh::Vector4(mShadowFar, mFadeStart * mShadowFar, 0, 0);
    sh::Factory::getInstance ().setSharedParameter ("shadowFar_fadeStart", sh::makeProperty<sh::Vector4>(shadowFar_fadeStart));

    // Set visibility mask for the shadow render textures
    int visibilityMask = RV_Actors * Settings::Manager::getBool("actor shadows", "Shadows")
                            + (RV_Statics + RV_StaticsSmall) * Settings::Manager::getBool("statics shadows", "Shadows")
                            + RV_Misc * Settings::Manager::getBool("misc shadows", "Shadows")
            + RV_Terrain * (Settings::Manager::getBool("terrain shadows", "Shadows"));
    for (int i = 0; i < splitsCount; ++i)
    {
        TexturePtr shadowTexture = mSceneMgr->getShadowTexture(i);
        Viewport* vp = shadowTexture->getBuffer()->getRenderTarget()->getViewport(0);
        vp->setVisibilityMask(visibilityMask);
    }

    // --------------------------------------------------------------------------------------------------------------------
    // --------------------------- Debug overlays to display the content of shadow maps -----------------------------------
    // --------------------------------------------------------------------------------------------------------------------
    /*
    if (Settings::Manager::getBool("debug", "Shadows"))
    {
        OverlayManager& mgr = OverlayManager::getSingleton();
        Overlay* overlay;

        // destroy if already exists
        if ((overlay = mgr.getByName("DebugOverlay")))
            mgr.destroy(overlay);

        overlay = mgr.create("DebugOverlay");
        for (size_t i = 0; i < (split ? 3 : 1); ++i) {
            TexturePtr tex = mRendering->getScene()->getShadowTexture(i);

            // Set up a debug panel to display the shadow

            if (MaterialManager::getSingleton().resourceExists("Ogre/DebugTexture" + StringConverter::toString(i)))
                MaterialManager::getSingleton().remove("Ogre/DebugTexture" + StringConverter::toString(i));
            MaterialPtr debugMat = MaterialManager::getSingleton().create(
                "Ogre/DebugTexture" + StringConverter::toString(i),
                ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

            debugMat->getTechnique(0)->getPass(0)->setLightingEnabled(false);
            TextureUnitState *t = debugMat->getTechnique(0)->getPass(0)->createTextureUnitState(tex->getName());
            t->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);

            OverlayContainer* debugPanel;

            // destroy container if exists
            try
            {
                if ((debugPanel =
                    static_cast<OverlayContainer*>(
                        mgr.getOverlayElement("Ogre/DebugTexPanel" + StringConverter::toString(i)
                    ))))
                    mgr.destroyOverlayElement(debugPanel);
            }
            catch (Ogre::Exception&) {}

            debugPanel = (OverlayContainer*)
                (OverlayManager::getSingleton().createOverlayElement("Panel", "Ogre/DebugTexPanel" + StringConverter::toString(i)));
            debugPanel->_setPosition(0.8, i*0.25);
            debugPanel->_setDimensions(0.2, 0.24);
            debugPanel->setMaterialName(debugMat->getName());
            debugPanel->show();
            overlay->add2D(debugPanel);
            overlay->show();
        }
    }
    else
    {
        OverlayManager& mgr = OverlayManager::getSingleton();
        Overlay* overlay;

        if ((overlay = mgr.getByName("DebugOverlay")))
            mgr.destroy(overlay);
    }
    */
}

PSSMShadowCameraSetup* Shadows::getPSSMSetup()
{
    return mPSSMSetup;
}

float Shadows::getShadowFar() const
{
    return mShadowFar;
}

float Shadows::getFadeStart() const
{
    return mFadeStart;
}
