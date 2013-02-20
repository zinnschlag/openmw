/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SH_MATERIALINSTANCEPASS_H
#define SH_MATERIALINSTANCEPASS_H

#include <vector>

#include "PropertyBase.hpp"
#include "MaterialInstanceTextureUnit.hpp"

namespace sh
{
	/**
	 * @brief
	 * Holds properties of a single texture unit in a \a MaterialInstancePass. \n
	 * No inheritance here for now.
	 */
	class MaterialInstancePass : public PropertySetGet
	{
	public:
		MaterialInstanceTextureUnit* createTextureUnit (const std::string& name);

		PropertySetGet mShaderProperties;

		std::vector <MaterialInstanceTextureUnit> getTexUnits ();
	private:
		std::vector <MaterialInstanceTextureUnit> mTexUnits;
	};
}

#endif
