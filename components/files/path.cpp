#include "path.hpp"

#include <boost/filesystem.hpp>

#include <OgrePlatform.h>
#include <string>

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#include <OSX/macUtils.h>
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX || OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#include <stdlib.h> //getenv
#endif

std::string Files::getPath (PathTypeEnum parType, const std::string parApp, const std::string parFile)
{
    std::string theBasePath;
    if (parType==Path_ConfigGlobal)
    {
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    	boost::filesystem::path path(Ogre::macBundlePath());
    	path = path.parent_path();
        theBasePath = path.string() + "/";
#elif OGRE_PLATFORM == OGRE_PLATFORM_LINUX
        theBasePath = "/etc/"+parApp+"/";
#else
        theBasePath = "";
#endif

    }
    else if (parType==Path_ConfigUser)
    {
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX || OGRE_PLATFORM == OGRE_PLATFORM_APPLE
        const char* theDir;
        if ((theDir = getenv("OPENMW_HOME")) != NULL)
        {
            theBasePath = std::string(theDir)+"/";
        }
        else
        {
            if ((theDir = getenv("XDG_CONFIG_HOME")))
            {
                theBasePath = std::string(theDir)+"/"+parApp+"/";
            }
            else
            {
                if ((theDir = getenv("HOME")) == NULL)
                    return parFile;
                theBasePath = std::string(theDir)+"/.config/"+parApp+"/";
            }
        }
        boost::filesystem::create_directories(boost::filesystem::path(theBasePath));
#else
        theBasePath = "";
#endif
    }

    theBasePath.append(parFile);
    std::cout << "theBasePath is " << theBasePath << std::endl;
    return theBasePath;
}
