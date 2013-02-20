/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SH_OGREPASS_H
#define SH_OGREPASS_H

#include <OgrePass.h>

#include "../../Main/Platform.hpp"

namespace sh
{
	class OgreMaterial;

	class OgrePass : public Pass
	{
	public:
		OgrePass (OgreMaterial* parent, const std::string& configuration, unsigned short lodIndex);

		virtual boost::shared_ptr<TextureUnitState> createTextureUnitState ();
		virtual void assignProgram (GpuProgramType type, const std::string& name);

		Ogre::Pass* getOgrePass();

		virtual void setGpuConstant (int type, const std::string& name, ValueType vt, PropertyValuePtr value, PropertySetGet* context);

		virtual void addSharedParameter (int type, const std::string& name);
		virtual void setTextureUnitIndex (int programType, const std::string& name, int index);

	private:
		Ogre::Pass* mPass;

	protected:
		virtual bool setPropertyOverride (const std::string &name, PropertyValuePtr& value, PropertySetGet* context);
	};
}

#endif
