#ifndef OENGINE_OGRE_RENDERER_H
#define OENGINE_OGRE_RENDERER_H

/*
  Ogre renderer class
 */

#include <string>

// Static plugin headers
#ifdef ENABLE_PLUGIN_CgProgramManager
# include "OgreCgPlugin.h"
#endif
#ifdef ENABLE_PLUGIN_OctreeSceneManager
# include "OgreOctreePlugin.h"
#endif
#ifdef ENABLE_PLUGIN_ParticleFX
# include "OgreParticleFXPlugin.h"
#endif
#ifdef ENABLE_PLUGIN_GL
# include "OgreGLPlugin.h"
#endif
#ifdef ENABLE_PLUGIN_Direct3D9
# include "OgreD3D9Plugin.h"
#endif

namespace Ogre
{
    class Root;
    class RenderWindow;
    class SceneManager;
    class Camera;
    class Viewport;
}

namespace OEngine {
namespace Render
{
  class Fader;
  class OgreRenderer
  {
    Ogre::Root *mRoot;
    Ogre::RenderWindow *mWindow;
    Ogre::SceneManager *mScene;
    Ogre::Camera *mCamera;
    Ogre::Viewport *mView;
	#ifdef ENABLE_PLUGIN_CgProgramManager
 	Ogre::CgPlugin* mCgPlugin;
 	#endif
 	#ifdef ENABLE_PLUGIN_OctreeSceneManager
 	Ogre::OctreePlugin* mOctreePlugin;
 	#endif
 	#ifdef ENABLE_PLUGIN_ParticleFX
 	Ogre::ParticleFXPlugin* mParticleFXPlugin;
 	#endif
 	#ifdef ENABLE_PLUGIN_GL
 	Ogre::GLPlugin* mGLPlugin;
 	#endif
	#ifdef ENABLE_PLUGIN_Direct3D9
 	Ogre::D3D9Plugin* mD3D9Plugin;
 	#endif
    Fader* mFader;
    bool logging;

  public:
    OgreRenderer()
      : mRoot(NULL), mWindow(NULL), mScene(NULL), mFader(NULL) {}
    ~OgreRenderer() { cleanup(); }

    /** Configure the renderer. This will load configuration files and
        set up the Root and logging classes. */
    bool configure(bool showConfig,     // Show config dialog box?
                   const std::string &cfgPath, // Path to directory where to store config files
                   const std::string &logPath, // Path to directory where to store log files
                   const std::string &pluginCfg, // plugin.cfg file
                   bool _logging);      // Enable or disable logging

    bool configure(bool showConfig,     // Show config dialog box?
                   const std::string &cfgPath, // Path to directory where to store config files
                   const std::string &pluginCfg, // plugin.cfg file
                   bool _logging);      // Enable or disable logging

    /** Configure the renderer. This will load configuration files and
        set up the Root and logging classes. */
    bool configure(bool showConfig,     // Show config dialog box?
                   const std::string &pluginCfg, // plugin.cfg file
                   bool _logging);      // Enable or disable logging

    /// Create a window with the given title
    void createWindow(const std::string &title);

    /// Set up the scene manager, camera and viewport
    void createScene(const std::string camName="Camera",// Camera name
                     float fov=55,                      // Field of view angle
                     float nearClip=5                   // Near clip distance
                     );

    /// Kill the renderer.
    void cleanup();

    /// Start the main rendering loop
    void start();

    bool loadPlugins();
    
    void update(float dt);

    /// Write a screenshot to file
    void screenshot(const std::string &file);

    float getFPS();

    /// Get the Root
    Ogre::Root *getRoot() { return mRoot; }

    /// Get the rendering window
    Ogre::RenderWindow *getWindow() { return mWindow; }

    /// Get the scene manager
    Ogre::SceneManager *getScene() { return mScene; }
    
    /// Get the screen colour fader
    Fader *getFader() { return mFader; }

    /// Camera
    Ogre::Camera *getCamera() { return mCamera; }

    /// Viewport
    Ogre::Viewport *getViewport() { return mView; }
  };
}}
#endif
