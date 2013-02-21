/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SH_SHADERINSTANCE_H
#define SH_SHADERINSTANCE_H

#include <vector>

#include "Platform.hpp"

namespace sh
{
	class ShaderSet;

	typedef std::map< std::string, std::pair<std::string, ValueType > > UniformMap;

	struct Passthrough
	{
		Language lang; ///< language to generate for

		int num_components; ///< e.g. 4 for a float4

		int passthrough_number;
		int component_start; ///< 0 = x

		std::string expand_assign(std::string assignTo);
		std::string expand_receive();
	};
	typedef std::map<std::string, Passthrough> PassthroughMap;

	/**
	 * @brief A specific instance of a \a ShaderSet with a deterministic shader source
	 */
	class ShaderInstance
	{
	public:
		ShaderInstance (ShaderSet* parent, const std::string& name, PropertySetGet* properties);

		std::string getName();

		bool getSupported () const;

		std::vector<std::string> getUsedSamplers();
		std::vector<std::string> getSharedParameters() { return mSharedParameters; }

		void setUniformParameters (boost::shared_ptr<Pass> pass, PropertySetGet* properties);

	private:
		boost::shared_ptr<GpuProgram> mProgram;
		std::string mName;
		ShaderSet* mParent;
		bool mSupported; ///< shader compilation was sucessful?

		std::vector<std::string> mUsedSamplers;
		///< names of the texture samplers that are used by this shader

		std::vector<std::string> mSharedParameters;

		UniformMap mUniformProperties;
		///< uniforms that this depends on, and their property names / value-types
		/// @note this lists shared uniform parameters as well

		int mCurrentPassthrough; ///< 0 - x
		int mCurrentComponent; ///< 0:x, 1:y, 2:z, 3:w

		PassthroughMap mPassthroughMap;

		std::vector<std::string> extractMacroArguments (size_t pos, const std::string& source); ///< take a macro invocation and return vector of arguments

		void parse (std::string& source, PropertySetGet* properties);
	};
}

#endif
