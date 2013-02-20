/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SH_OGREGPUPROGRAM_H
#define SH_OGREGPUPROGRAM_H

#include <string>

#include <OgreHighLevelGpuProgram.h>

#include "../../Main/Platform.hpp"

namespace sh
{
	class OgreGpuProgram : public GpuProgram
	{
	public:
		OgreGpuProgram (
			GpuProgramType type,
			const std::string& compileArguments,
			const std::string& name, const std::string& profile,
			const std::string& source, const std::string& lang,
			const std::string& resourceGroup);

		virtual bool getSupported();

		virtual void setAutoConstant (const std::string& name, const std::string& autoConstantName, const std::string& extraInfo = "");

	private:
		Ogre::HighLevelGpuProgramPtr mProgram;
	};
}

#endif
