/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SH_MATERIALINSTANCETEXTUREUNIT_H
#define SH_MATERIALINSTANCETEXTUREUNIT_H

#include "PropertyBase.hpp"

namespace sh
{
	/**
	 * @brief
	 * A single texture unit state that belongs to a \a MaterialInstancePass \n
	 * this is not the real "backend" \a TextureUnitState (provided by \a Platform),
	 * it is merely a placeholder for properties. \n
	 * @note The backend \a TextureUnitState will only be created if this texture unit is
	 * actually used (i.e. referenced in the shader, or marked with property create_in_ffp = true).
	 */
	class MaterialInstanceTextureUnit : public PropertySetGet
	{
	public:
		MaterialInstanceTextureUnit (const std::string& name);
		std::string getName() const;
	private:
		std::string mName;
	};
}

#endif
