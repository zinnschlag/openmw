/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SH_OGREMATERIAL_H
#define SH_OGREMATERIAL_H

#include <string>

#include <OgreMaterial.h>

#include "../../Main/Platform.hpp"

namespace sh
{
	class OgreMaterial : public Material
	{
	public:
		OgreMaterial (const std::string& name, const std::string& resourceGroup);
		virtual ~OgreMaterial();

		virtual boost::shared_ptr<Pass> createPass (const std::string& configuration, unsigned short lodIndex);
		virtual bool createConfiguration (const std::string& name, unsigned short lodIndex);

		virtual void removeAll ();

		Ogre::MaterialPtr getOgreMaterial();

		virtual void setLodLevels (const std::string& lodLevels);

		Ogre::Technique* getOgreTechniqueForConfiguration (const std::string& configurationName, unsigned short lodIndex = 0);

		virtual void setShadowCasterMaterial (const std::string& name);

	private:
		Ogre::MaterialPtr mMaterial;

		std::string mShadowCasterMaterial;
	};
}

#endif
