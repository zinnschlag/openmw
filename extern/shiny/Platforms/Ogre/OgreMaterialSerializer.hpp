/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SH_OGREMATERIALSERIALIZER_H
#define SH_OGREMATERIALSERIALIZER_H

#include <OgreMaterialSerializer.h>

namespace Ogre
{
	class Pass;
}

namespace sh
{
	/**
	 * @brief This class allows me to let Ogre handle the pass & texture unit properties
	 */
	class OgreMaterialSerializer : public Ogre::MaterialSerializer
	{
	public:
		bool setPassProperty (const std::string& param, std::string value, Ogre::Pass* pass);
		bool setTextureUnitProperty (const std::string& param, std::string value, Ogre::TextureUnitState* t);
		bool setMaterialProperty (const std::string& param, std::string value, Ogre::MaterialPtr m);

	private:
		void reset();
	};

}

#endif
