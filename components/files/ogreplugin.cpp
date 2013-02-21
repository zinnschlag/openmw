/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "ogreplugin.hpp"

#include <OgrePrerequisites.h>
#include <OgreRoot.h>

namespace Files {

bool loadOgrePlugin(const std::string &pluginDir, std::string pluginName, Ogre::Root &ogreRoot) {
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
	std::ostringstream verStream;
	verStream << "." << OGRE_VERSION_MAJOR << "." << OGRE_VERSION_MINOR << "." << OGRE_VERSION_PATCH;
	pluginName = pluginName + verStream.str();
#endif

	std::string pluginExt;
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    pluginExt = ".dll";
#endif
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    pluginExt = ".dylib";
#endif
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
    pluginExt = ".so";
#endif

    // Append plugin suffix if debugging.
    std::string pluginPath;
#if defined(DEBUG)
    pluginPath = pluginDir + "/" + pluginName + OGRE_PLUGIN_DEBUG_SUFFIX + pluginExt;
    if (boost::filesystem::exists(pluginPath)) {
        ogreRoot.loadPlugin(pluginPath);
        return true;
    }
    else {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        return false;
#endif //OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    }
#endif //defined(DEBUG)
    
    pluginPath = pluginDir + "/" + pluginName + pluginExt;
    if (boost::filesystem::exists(pluginPath)) {
        ogreRoot.loadPlugin(pluginPath);
        return true;
    }
    else {
        return false;
    }
}

}