/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "OgreMaterialSerializer.hpp"

namespace sh
{
	void OgreMaterialSerializer::reset()
	{
		mScriptContext.section = Ogre::MSS_NONE;
		mScriptContext.material.setNull();
		mScriptContext.technique = 0;
		mScriptContext.pass = 0;
		mScriptContext.textureUnit = 0;
		mScriptContext.program.setNull();
		mScriptContext.lineNo = 0;
		mScriptContext.filename.clear();
		mScriptContext.techLev = -1;
		mScriptContext.passLev = -1;
		mScriptContext.stateLev = -1;
	}

	bool OgreMaterialSerializer::setPassProperty (const std::string& param, std::string value, Ogre::Pass* pass)
	{
		reset();

		mScriptContext.section = Ogre::MSS_PASS;
		mScriptContext.pass = pass;

		if (mPassAttribParsers.find (param) == mPassAttribParsers.end())
			return false;
		else
		{
			mPassAttribParsers.find(param)->second(value, mScriptContext);
			return true;
		}
	}

	bool OgreMaterialSerializer::setTextureUnitProperty (const std::string& param, std::string value, Ogre::TextureUnitState* t)
	{
		reset();

		mScriptContext.section = Ogre::MSS_TEXTUREUNIT;
		mScriptContext.textureUnit = t;

		if (mTextureUnitAttribParsers.find (param) == mTextureUnitAttribParsers.end())
			return false;
		else
		{
			mTextureUnitAttribParsers.find(param)->second(value, mScriptContext);
			return true;
		}
	}

	bool OgreMaterialSerializer::setMaterialProperty (const std::string& param, std::string value, Ogre::MaterialPtr m)
	{
		reset();

		mScriptContext.section = Ogre::MSS_MATERIAL;
		mScriptContext.material = m;

		if (mMaterialAttribParsers.find (param) == mMaterialAttribParsers.end())
			return false;
		else
		{
			mMaterialAttribParsers.find(param)->second(value, mScriptContext);
			return true;
		}
	}
}
