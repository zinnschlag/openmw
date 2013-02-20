/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OENGINE_OGRE_IMAGEROTATE_HPP
#define OENGINE_OGRE_IMAGEROTATE_HPP

#include <string>

namespace OEngine
{
namespace Render
{

    /// Rotate an image by certain degrees and save as file, uses the GPU
    /// Make sure Ogre Root is initialised before calling
    class ImageRotate
    {
    public:
        /**
         * @param source image (file name - has to exist in an resource group)
         * @param name of the destination texture to save to (in memory)
         * @param angle in degrees to turn
         */
        static void rotate(const std::string& sourceImage, const std::string& destImage, const float angle);
    };

}
}

#endif
