/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SH_OGREPLATFORM_H
#define SH_OGREPLATFORM_H

/**
 * @addtogroup Platforms
 * @{
 */

/**
 * @addtogroup Ogre
 * A set of classes to interact with Ogre's material system
 * @{
 */

#include "../../Main/Platform.hpp"

#include <OgreMaterialManager.h>
#include <OgreGpuProgramParams.h>

namespace sh
{
	class OgreMaterialSerializer;

	class OgrePlatform : public Platform, public Ogre::MaterialManager::Listener
	{
	public:
		OgrePlatform (const std::string& resourceGroupName, const std::string& basePath);
		virtual ~OgrePlatform ();

		virtual Ogre::Technique* handleSchemeNotFound (
			unsigned short schemeIndex, const Ogre::String &schemeName, Ogre::Material *originalMaterial,
			unsigned short lodIndex, const Ogre::Renderable *rend);

		static OgreMaterialSerializer& getSerializer();

	private:
		virtual bool isProfileSupported (const std::string& profile);

		virtual void serializeShaders (const std::string& file);
		virtual void deserializeShaders (const std::string& file);

		virtual boost::shared_ptr<Material> createMaterial (const std::string& name);

		virtual boost::shared_ptr<GpuProgram> createGpuProgram (
			GpuProgramType type,
			const std::string& compileArguments,
			const std::string& name, const std::string& profile,
			const std::string& source, Language lang);

		virtual void setSharedParameter (const std::string& name, PropertyValuePtr value);

		friend class ShaderInstance;
		friend class Factory;

	protected:
		virtual bool supportsShaderSerialization ();
		virtual bool supportsMaterialQueuedListener ();

		std::string mResourceGroup;

		static OgreMaterialSerializer* sSerializer;

		std::map <std::string, Ogre::GpuSharedParametersPtr> mSharedParameters;
	};
}

/**
 * @}
 * @}
 */

#endif
