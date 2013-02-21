/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SH_OGRETEXTUREUNITSTATE_H
#define SH_OGRETEXTUREUNITSTATE_H

#include <OgreTextureUnitState.h>

#include "../../Main/Platform.hpp"

namespace sh
{
	class OgrePass;

	class OgreTextureUnitState : public TextureUnitState
	{
	public:
		OgreTextureUnitState (OgrePass* parent);

		virtual void setTextureName (const std::string& textureName);

	private:
		Ogre::TextureUnitState* mTextureUnitState;

	protected:
		virtual bool setPropertyOverride (const std::string &name, PropertyValuePtr& value, PropertySetGet* context);
	};
}

#endif
